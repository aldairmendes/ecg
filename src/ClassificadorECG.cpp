#include "ClassificadorECG.h"
#include <iostream>

// Construtor (precisa ser implementado se estiver no .h)
ClassificadorECG::ClassificadorECG() {
    // Inicialização se necessário
}

void ClassificadorECG::processarAmostra(float valorBruto) {
    float valorNormalizado = normalizar(valorBruto);
    janelaSinal.push_back(valorNormalizado);

    if (janelaSinal.size() >= TAMANHO_JANELA) {
        std::string resultado = classificar();
        std::cout << "Classificação: " << resultado << std::endl;
        janelaSinal.clear();
    }
}

float ClassificadorECG::normalizar(float entrada) {
    return entrada; 
}

std::string ClassificadorECG::classificar() {
    return "Sinal Normal";
}