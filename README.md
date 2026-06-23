# Projeto Classificador ECG

Este projeto contém um classificador de sinais de ECG com duas partes principais:
- `ecg/sensor/capture_signal.ino`: sketch Arduino para ESP32 que captura sinais ECG do ADC e envia valores pela porta serial.
- `ecg/`: aplicação C++ e scripts Python para receber dados seriais, processar janelas de ECG e classificar os sinais.

## Estrutura principal

- `ecg/`: diretório do projeto de classificação.
  - `src/`: código-fonte C++ do programa de desktop.
    - `main.cpp`: lê dados da porta serial, grava CSV opcional e envia amostras para o classificador.
    - `ClassificadorECG.cpp` / `ClassificadorECG.h`: acumula 187 amostras, normaliza e chama o modelo.
    - `modelo_ecg_export.cpp`: implementação C++ gerada do modelo treinado, com a função `score()` que classifica um vetor de 187 amostras.
    - `SerialPort.cpp`: interface serial Windows para ler o ESP32.
    - `EcgBuffer.cpp` / `EcgBuffer.h`: buffer circular de amostras ECG.
  - `sensor/capture_signal.ino`: sketch para ESP32 que lê o valor analógico e envia números pela serial.
  - `treinar.py`: script Python que treina um modelo RandomForest usando os dados em `ecg/data/`.
  - `live_plot.py`: script Python para plotar os dados recebidos em tempo real.
  - `requirements.txt`: dependências Python.

## Como executar

### 1. Instalar dependências Python

Abra um terminal no diretório `ecg/` e instale as bibliotecas:

```bash
python -m pip install -r ecg/requirements.txt
```

### 2. Carregar o sketch no ESP32

- Abra `ecg/sensor/capture_signal.ino` no Arduino IDE ou PlatformIO.
- Configure a placa `esp32dev` e a porta COM correta.
- Carregue o sketch no ESP32.
- O sketch lê o pino ADC `36` e imprime um valor numérico a cada ~15 ms.

### 3. Compilar e executar a aplicação C++

A aplicação C++ está configurada em `ecg/CMakeLists.txt`. No Windows, use CMake para gerar o projeto e compilar:

```bash
cd ecg
mkdir -p build
cd build
cmake ..
cmake --build . --config Release
```

Depois, execute o arquivo gerado `programa_ecg`:

```bash
cd ecg/build/Release
programa_ecg COM3 dados.csv --label 0 --plot --plot-script ../live_plot.py
```

Substitua `COM3` pela porta serial correta do ESP32.

### 3.1 Executar os testes

Após compilar com CMake, execute o binário de testes para validar o código:

```bash
cd ecg/build/Release
executa_testes
```

Ou use CTest no diretório de build:

```bash
cd ecg/build
ctest -C Release
```

Esse processo executa os testes definidos em `ecg/tests/test_main.cpp` contra o código de classificação.

#### Argumentos úteis

- `COM3`: porta serial do ESP32.
- `dados.csv`: arquivo opcional para salvar cada janela de 187 amostras.
- `--label 0`: etiqueta para os dados salvos em CSV.
- `--plot`: habilita o gráfico em tempo real usando `live_plot.py`.
- `--plot-script ../live_plot.py`: caminho do script Python de plot.
- `--plot-window 5`: janela de visualização em segundos.
- `--plot-fs 250`: frequência de amostragem usada pelo plot.

### 4. Usar o plot em tempo real

Se `--plot` estiver habilitado, o `programa_ecg` abre um processo Python que escreve no plot em tempo real. Verifique se o Python está disponível no `PATH` e se `live_plot.py` está no caminho correto.

## Parte do modelo

### Como o modelo funciona

O classificador usa uma janela de 187 amostras consecutivas do sinal ECG. Essas amostras são normalizadas para o intervalo `[0, 1]` pela classe `ClassificadorECG` antes de serem passadas ao modelo.

Em `ecg/src/ClassificadorECG.cpp`:
- `processarAmostra()`: acumula amostras até formar uma janela completa.
- `normalizar()`: divide por `4095.0` quando o valor é maior que 1.0, convertendo a leitura do ADC para [0, 1].
- `classificar()`: chama `score()` e escolhe a classe com maior probabilidade.

### Modelo exportado

`ecg/src/modelo_ecg_export.cpp` contém a implementação do modelo diretamente em código C++. A função `score(const double* input, double* output)` recebe um vetor de 187 valores normalizados e define cinco saídas correspondentes a classes:

- `0`: Normal
- `1`: Arritmia supraventricular
- `2`: Batimento ventricular
- `3`: Fusão de batimentos
- `4`: Batimento desconhecido

O modelo já está convertido em código C++ para ser executado localmente sem dependências externas de machine learning.

### Treinamento do modelo

O script `ecg/treinar.py` treina um `RandomForestClassifier` usando os arquivos:
- `ecg/data/mitbih_train.csv`
- `ecg/data/mitbih_test.csv`

Esses arquivos têm 187 colunas de sinais ECG e uma coluna final de rótulo.

O script realiza:
1. leitura dos CSVs;
2. separação de `X` e `y`;
3. treinamento do Random Forest;
4. avaliação de acurácia e relatório de classificação;
5. salvamento do modelo em `ecg/data/modelo_ecg.pkl`.

## Observações finais

- Feche o Monitor Serial do Arduino IDE antes de executar `programa_ecg`; caso contrário, a porta serial pode ficar ocupada.
- O projeto usa `windows.h` e `CreateFileA`, então a aplicação C++ deve ser executada no Windows.
- `ecg/sensor/capture_signal.ino` já imprime apenas valores numéricos, o que facilita a leitura serial pela aplicação.

Se precisar, posso também criar um `README` específico dentro de `ecg/` com instruções separadas para PC e ESP32.
