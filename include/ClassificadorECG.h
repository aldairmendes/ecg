#ifndef CLASSIFICADOR_ECG_H
#define CLASSIFICADOR_ECG_H

#include <vector>
#include <string>

class ClassificadorECG {
private:
    std::vector<float> janelaSinal;
    const std::size_t TAMANHO_JANELA = 500;

public:
    // Construtor (opcional, mas boa prática)
    ClassificadorECG();

    // Processa o dado vindo do sensor
    void processarAmostra(float valorBruto);

    // Normalização do sinal
    float normalizar(float entrada);

    // Classificação da janela atual
    std::string classificar();
};

#endif