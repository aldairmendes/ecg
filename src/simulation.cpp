#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include "ClassificadorECG.h"

int main() {
    ClassificadorECG classificador;

    std::string filePath = "data/mitbih_test.csv";
    std::ifstream dataset(filePath);

    if (!dataset.is_open()) {
        std::cerr << "Erro: nao foi possivel abrir " << filePath << std::endl;
        return 1;
    }

    int total         = 0;
    int corretos      = 0;
    int erros         = 0;
    int debugArritmias = 0;
    std::string linha;

    std::cout << "Iniciando simulacao: " << filePath << std::endl;

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

        if ((int)amostras.size() != 187 || groundTruth < 0) {
            erros++;
            continue;
        }

        for (float v : amostras)
            classificador.processarAmostra(v);

        int64_t predito = classificador.getUltimaClasse();

        if (groundTruth > 0 && debugArritmias < 10) {
            std::cout << "Arritmia " << debugArritmias
                      << " | ground=" << groundTruth
                      << " | cpp=" << predito << "\n";
            debugArritmias++;
        }

        int predBin  = (predito  > 0) ? 1 : 0;
        int truthBin = (groundTruth > 0) ? 1 : 0;

        if (predBin == truthBin) corretos++;
        total++;

        if (total % 1000 == 0)
            std::cout << "  " << total << " batimentos processados...\n";
    }

    dataset.close();

    std::cout << "\n=== Resultado ===\n";
    std::cout << "Total de batimentos : " << total     << "\n";
    std::cout << "Classificados certo : " << corretos  << "\n";
    std::cout << "Linhas ignoradas    : " << erros     << "\n";
    if (total > 0) {
        double acuracia = 100.0 * corretos / total;
        std::cout << "Acuracia            : " << acuracia << "%\n";

        if (acuracia >= 95.0)
            std::cout << "Status: OK — pipeline funcionando corretamente.\n";
        else if (acuracia >= 80.0)
            std::cout << "Status: ATENCAO — acuracia abaixo do esperado (>97%).\n";
        else
            std::cout << "Status: ERRO — possivel problema no modelo ou nos dados.\n";
    }

    return 0;
}
