#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include "main.cpp"

int main() {
    ClassificadorECG meuClassificador;
    
    std::string filePath = "data/mitbih_test.csv"; 
    std::ifstream dataset(filePath);

    if (!dataset.is_open()) {
        std::cerr << "Erro: Nao foi possivel encontrar o arquivo " << filePath << std::endl;
        return 1;
    }

    std::string linha;
    std::cout << "Simulando entrada de dados pelo dataset: " << filePath << std::endl;

    // Lendo o dataset linha por linha (cada linha costuma ser um sinal completo no MIT-BIH)
    while (std::getline(dataset, linha)) {
        std::stringstream ss(linha);
        std::string valorStr;

        // No dataset MIT-BIH, os valores são separados por vírgula
        while (std::getline(ss, valorStr, ',')) {
            try {
                float valorSinal = std::stof(valorStr);
                
                // Envia para o seu pipeline de tratamento e classificação
                meuClassificador.processarAmostra(valorSinal);
                
            } catch (...) {
                continue;
            }
        }
    }

    std::cout << "Simulacao concluida!" << std::endl;
    return 0;
}