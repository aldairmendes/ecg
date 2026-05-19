#include "ClassificadorECG.h"
#include "modelo_ecg_export.h"
#include <iostream>
#include <algorithm>

ClassificadorECG::ClassificadorECG() = default;

void ClassificadorECG::processarAmostra(float valorBruto) {
    float valorNormalizado = normalizar(valorBruto);
    janelaSinal.push_back(valorNormalizado);

    if (janelaSinal.size() >= TAMANHO_JANELA) {
        std::string resultado = classificar();
        std::cout << "Classificacao: " << resultado << std::endl;
        std::cout.flush();
        janelaSinal.clear();
    }
}

float ClassificadorECG::normalizar(float entrada) {
    return entrada;
}

int ClassificadorECG::classificar(const std::vector<float>& sinal) {
    std::vector<double> entrada(sinal.size());
    for (std::size_t i = 0; i < sinal.size(); ++i) {
        entrada[i] = static_cast<double>(normalizar(sinal[i]));
    }

    double saida[5] = {0};
    score(entrada.data(), saida);

    int classe = 0;
    for (int i = 1; i < 5; ++i) {
        if (saida[i] > saida[classe]) {
            classe = i;
        }
    }
    return classe;
}

std::string ClassificadorECG::classificar() {
    static const char* nomes[] = {
        "Normal", "Arritmia supraventricular", "Batimento ventricular",
        "Fusao de batimentos", "Batimento desconhecido"
    };
    int cls = classificar(janelaSinal);
    if (cls >= 0 && cls < 5) {
        return nomes[cls];
    }
    return "Desconhecido";
}
