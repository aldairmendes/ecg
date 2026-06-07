#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "ClassificadorECG.h"

// Roda o classificador contra o CSV do MIT-BIH e imprime a acurácia.
// Compile com: make simulation
// Execute com: ./bin/simulacao

int main() {
    ClassificadorECG classificador;

    const std::string filePath = "data/dados.csv";
    std::ifstream dataset(filePath);
    if (!dataset.is_open()) {
        std::cerr << "Erro: nao foi possivel abrir " << filePath << "\n"
                  << "Verifique se o arquivo existe em data/mitbih_test.csv\n";
        return 1;
    }

    int total          = 0;
    int corretos       = 0;
    int erros          = 0;
    int debugArritmias = 0;
    std::string linha;

    std::cout << "Iniciando simulacao com: " << filePath << "\n";

    while (std::getline(dataset, linha)) {
        if (linha.empty()) continue;

        std::stringstream ss(linha);
        std::string valorStr;
        std::vector<float> amostras;
        int groundTruth = -1;
        int coluna = 0;

        while (std::getline(ss, valorStr, ',')) {
            try {
                float v = std::stof(valorStr);
                if (coluna < 187)
                    amostras.push_back(v);
                else if (coluna == 187)
                    groundTruth = static_cast<int>(v);
            } catch (...) {}
            coluna++;
        }

        if (static_cast<int>(amostras.size()) != 187 || groundTruth < 0) {
            erros++;
            continue;
        }

        // Classifica o sinal diretamente (os dados do MIT-BIH já estão em [0,1])
        int predito = classificador.classificar(amostras);

        // Debug das primeiras arritmias para inspeção manual
        if (groundTruth > 0 && debugArritmias < 10) {
            std::cout << "Arritmia " << debugArritmias
                      << " | ground=" << groundTruth
                      << " | predito=" << predito << "\n";
            debugArritmias++;
        }

        // Avaliação binária: Normal (0) vs Qualquer Arritmia (1+)
        int predBin  = (predito  > 0) ? 1 : 0;
        int truthBin = (groundTruth > 0) ? 1 : 0;
        if (predBin == truthBin) corretos++;
        total++;

        if (total % 1000 == 0)
            std::cout << "  " << total << " batimentos processados...\n";
    }

    dataset.close();

    std::cout << "\n=== Resultado ===\n";
    std::cout << "Total de batimentos : " << total    << "\n";
    std::cout << "Classificados certo : " << corretos << "\n";
    std::cout << "Linhas ignoradas    : " << erros    << "\n";

    if (total > 0) {
        const double acuracia = 100.0 * corretos / total;
        std::cout << "Acuracia binaria    : " << acuracia << "%\n";

        if (acuracia >= 95.0)
            std::cout << "Status: OK - pipeline funcionando corretamente.\n";
        else if (acuracia >= 80.0)
            std::cout << "Status: ATENCAO - acuracia abaixo do esperado (>95%).\n";
        else
            std::cout << "Status: ERRO - possivel problema no modelo ou nos dados.\n";
    }

    return 0;
}