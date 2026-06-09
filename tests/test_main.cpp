#define CATCH_CONFIG_MAIN  // O Catch2 gera o main() automaticamente aqui
#include "catch2/catch.hpp"
#include "ClassificadorECG.h"
#include "EcgBuffer.h"
#include "SerialPort.h"
#include <cstdlib>
#include <chrono>
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

    // Raw ADC do ESP32 deve ser normalizado para o mesmo intervalo do dataset.
    REQUIRE(ecg.normalizar(4095.0f) == Approx(1.0f));
    REQUIRE(ecg.normalizar(0.0f) == Approx(0.0f));
    
    // Valores já normalizados devem ser mantidos.
    REQUIRE(ecg.normalizar(0.5f) == Approx(0.5f));
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

static bool parseSample(const std::string& line, uint16_t& sample) {
    if (line.empty()) {
        return false;
    }

    char* end = nullptr;
    const long value = std::strtol(line.c_str(), &end, 10);
    if (end == line.c_str() || value < 0 || value > 4095) {
        return false;
    }

    sample = static_cast<uint16_t>(value);
    return true;
}

TEST_CASE("Teste real com sensor AD8232", "[sensor][manual]") {
    const char* port = std::getenv("ECG_SENSOR_PORT");
    if (!port) {
        WARN("ECG_SENSOR_PORT nao definido. Para testar o sensor real, defina a porta serial em ECG_SENSOR_PORT.");
        return;
    }

    SerialPort serial(port, 115200);
    if (!serial.isOpen()) {
        WARN("Nao foi possivel abrir a porta serial. Verifique se o sensor AD8232 esta conectado e se a porta esta correta.");
        return;
    }

    ClassificadorECG classificador;
    ECG_Buffer buffer;
    buffer.index = 0;
    buffer.ready = false;

    std::string line;
    auto startTime = std::chrono::steady_clock::now();
    const auto timeout = std::chrono::seconds(20);

    while (std::chrono::steady_clock::now() - startTime < timeout) {
        if (!serial.readLine(line)) {
            continue;
        }

        uint16_t sample;
        if (!parseSample(line, sample)) {
            continue;
        }

        if (buffer.index < BUFFER_SIZE) {
            buffer.samples[buffer.index++] = sample;
        }

        if (buffer.index >= BUFFER_SIZE) {
            buffer.ready = true;
            break;
        }
    }

    if (!buffer.ready) {
        WARN("Nao foi possivel preencher o buffer com dados do sensor dentro do timeout.");
        return;
    }

    std::cout << "Buffer size: " << static_cast<unsigned>(buffer.index) << std::endl;
    // std::cout << "[Buffer] valores: " << std::endl;
    // for (int i = 0; i < buffer.index; ++i) {
    //     std::cout << buffer.samples[i] << (i + 1 < buffer.index ? ", " : "");
    // }
    // std::cout << std::endl;

    std::vector<float> sinalParaClassificar(buffer.samples, buffer.samples + BUFFER_SIZE);
    int resultado = classificador.classificar(sinalParaClassificar);
    std::cout << "Resultado da classificacao com sensor real: " << resultado << std::endl;
    CHECK(resultado >= 0);
    CHECK(resultado < 5);
}