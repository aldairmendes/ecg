Como rodar os testes:

    Baixe as bibliotecas:
    
        sudo apt update && sudo apt install catch2 
        mkdir -p libs && cd libs
        wget https://github.com/microsoft/onnxruntime/releases/download/v1.20.1/onnxruntime-linux-x64-1.20.1.tgz
        tar -xvf onnxruntime-linux-x64-1.20.1.tgz
        wget https://github.com/catchorg/Catch2/releases/download/v2.13.10/catch.hpp -P include/

Treinando o modelo:

    Entre na venv:
    source venv/bin/activate

    Dentro da venv, dê esse comando:
        python3 treinar.py
        CTRL+D para sair

MAKEFILE

1. make: Comando principal. Ele olha para a variável TARGET (classificador_ecg).

    O que faz: Compila o código principal do sistema (main.cpp + ClassificadorECG.cpp).

    Fluxo: Ele gera arquivos intermediários .o na pasta src/ e depois "linka" tudo com a biblioteca ONNX Runtime para gerar o executável na raiz.

    Uso: Quando você quer gerar a versão final do classificador.

2. make test: Comando de verificação.

    O que faz: Compila o test_main.cpp

    Localização: O executável é guardado em bin/executa_testes.

3. make simulation: Comando focado em demonstração.

    O que faz: Usa o arquivo simulation.cpp para rodar uma simulação do comportamento do ECG (provavelmente lendo aqueles arquivos .csv que vi na sua pasta data/).

    Uso: Ideal para validar como o classificador se comporta com um fluxo contínuo de dados antes de testar no hardware real.

4. make clean: Comando de manutenção.

    O que faz: Remove todos os arquivos temporários (.o) e os binários gerados.

    Importância: Evita que erros de compilação antiga interfiram no código novo. É a primeira coisa que você deve rodar se o compilador começar a se comportar de forma estranha.

Variáveis Makefile:

    CXXFLAGS: São as opções enviadas ao compilador.

        -Wall: Ativa todos os avisos de erro (ajuda a evitar bugs).

        -std=c++17: Define a versão moderna do C++ exigida pelo ONNX.

        -Iinclude: Diz ao compilador para olhar dentro da sua pasta include/.

    LDFLAGS: São as opções de "linkagem" (conexão com bibliotecas externas).

        -L$(ONNX_DIR)/lib: Localiza onde estão os arquivos binários do ONNX.

        -lonnxruntime: Diz ao sistema para usar a biblioteca ONNX.

        -Wl,-rpath: Garante que, ao rodar o programa, ele saiba encontrar a biblioteca .so dentro da pasta libs/.