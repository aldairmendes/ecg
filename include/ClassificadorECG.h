#ifndef CLASSIFICADOR_ECG_H
#define CLASSIFICADOR_ECG_H

#include <vector>
#include <string>
#include <onnxruntime_cxx_api.h>

class ClassificadorECG {
public:
    ClassificadorECG();

    // Recebe uma amostra bruta do ADC (0-4095) e acumula na janela.
    // Quando a janela completar 187 amostras, classifica e imprime o resultado.
    void processarAmostra(float valorBruto);

    // Normaliza um valor bruto do ADC (0-4095) para [0.0, 1.0].
    // Valores já normalizados (ex: vindos do CSV MIT-BIH) passam direto.
    float normalizar(float entrada);

    // Classifica um sinal já montado como vetor de 187 floats normalizados.
    // Retorna: 0=Normal, 1=Supraventricular, 2=Ventricular, 3=Fusao, 4=Desconhecido, -1=Erro
    int classificar(const std::vector<float>& sinal);

    // Retorna a última classe inferida (útil para simulation.cpp).
    int64_t getUltimaClasse() const;

private:
    std::vector<float> janelaSinal;
    static constexpr std::size_t TAMANHO_JANELA = 187;

    Ort::Env     env;
    Ort::Session session;
    int64_t      ultimaClasse;

    // Sobrecarrega interna: classifica a janelaSinal atual e retorna string legível.
    std::string classificarJanela();
};

#endif