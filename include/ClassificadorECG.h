#ifndef CLASSIFICADOR_ECG_H
#define CLASSIFICADOR_ECG_H

#include <vector>
#include <string>

class ClassificadorECG {
private:
    std::vector<float> janelaSinal;
    static constexpr std::size_t TAMANHO_JANELA = 187;

public:
    ClassificadorECG();

    void processarAmostra(float valorBruto);
    float normalizar(float entrada);

    int classificar(const std::vector<float>& sinal);
    std::string classificar();
};

#endif
