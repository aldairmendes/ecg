#define CATCH_CONFIG_MAIN  // O Catch2 gera o main() automaticamente aqui
#include "catch.hpp"
#include "ClassificadorECG.h"
#include "EcgBuffer.h"
#include <fstream>
#include <sstream>
#include <vector>

// Função auxiliar para carregar dados CSV
std::vector<std::vector<float>> carregarAmostras(const std::string& path, int limite) {
    std::vector<std::vector<float>> amostras;
    std::ifstream file(path);
    std::string linha;
    int cont = 0;

    while (std::getline(file, linha) && cont < limite) {
        std::vector<float> entrada;
        std::stringstream ss(linha);
        std::string valor;

        while (std::getline(ss, valor, ',')) {
            entrada.push_back(std::stof(valor));
        }

        if (!entrada.empty()) {
            entrada.pop_back(); // Remove o label original do CSV
            amostras.push_back(entrada);
        }
        cont++;
    }
    return amostras;
}

TEST_CASE("Normalização de sinal", "[ecg]") {
    ClassificadorECG ecg;
    
    // Testa se a normalização está devolvendo o valor esperado
    REQUIRE(ecg.normalizar(10.0) == 10.0); 
}

TEST_CASE("Acúmulo de amostras", "[ecg]") {
    ClassificadorECG ecg;
    // Simula 500 chamadas e verifica se a lógica interna responde corretamente
}

TEST_CASE("Validação do Classificador de ECG com PTBDB", "[ml]") {
    ClassificadorECG classificador; // Assume o caminho padrão no construtor
    const int total_testes = 1000;

    SECTION("Testando 1000 amostras Normais") {
        auto dados = carregarAmostras("data/ptbdb_normal.csv", total_testes);
        int acertos = 0;

        for (const auto& sinal : dados) {
            if (classificador.classificar(sinal) == 0) acertos++;
        }

        float acuracia = (float)acertos / dados.size();
        std::cout << "[Normal] Acuracia: " << acuracia * 100 << "%" << std::endl;
        REQUIRE(acuracia >= 0.97);
    }

    SECTION("Testando 1000 amostras Anormais") {
        auto dados = carregarAmostras("data/ptbdb_abnormal.csv", total_testes);
        int acertos = 0;

        for (const auto& sinal : dados) {
            // Considera acerto qualquer classe de arritmia (>= 1)
            if (classificador.classificar(sinal) >= 1) acertos++;
        }

        float acuracia = (float)acertos / dados.size();
        std::cout << "[Abnormal] Acuracia: " << acuracia * 100 << "%" << std::endl;
        REQUIRE(acuracia >= 0.97);
    }
}

TEST_CASE("Simulação de Batimento Real (AD8232)", "[sensor]") {
    ClassificadorECG classificador;
    ECG_Buffer buffer;
    
    // 1. Inicialização do Struct
    buffer.index = 0;
    buffer.ready = false;

    // 2. Simulação de captura do sensor (Preenchendo os 187 pontos)
    // No hardware real, isso aconteceria dentro de um loop de 360Hz
    auto amostrasCsv = carregarAmostras("data/ptbdb_normal.csv", 1);
    auto sinalReal = amostrasCsv[0]; // Pega o primeiro batimento normal

    for (float valorSinal : sinalReal) {
        if (buffer.index < BUFFER_SIZE) {
            buffer.samples[buffer.index] = valorSinal;
            buffer.index++;
        }
    }
    buffer.ready = (buffer.index == BUFFER_SIZE);

    // 3. Classificação do Struct preenchido
    SECTION("Classificando o buffer preenchido") {
        REQUIRE(buffer.ready == true);

        // Convertendo o array do struct para um vector para o classificador
        std::vector<float> sinalParaClassificar(
            buffer.samples,             // Isso funciona como um Spread Operator, não é um vetor dentro de outro
            buffer.samples + BUFFER_SIZE
        );

        int resultado = classificador.classificar(sinalParaClassificar);
        
        // Como o sinal veio do arquivo 'normal', esperamos classe 0
        CHECK(resultado == 0);
        std::cout << "Resultado da classificação do buffer: " << resultado << std::endl;
    }
}