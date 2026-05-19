#include "ClassificadorECG.h"
#include "EcgBuffer.h"
#include "SerialPort.h"

#include <chrono>
#include <cstdlib>
#include <iostream>
#include <string>

namespace {

bool parseSample(const std::string& line, uint16_t& sample) {
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

void processFullBuffer(ECG_Buffer& buffer, ClassificadorECG& classificador) {
    std::cout << "Buffer cheio (" << BUFFER_SIZE << " amostras). Primeiras 5: ";
    for (int i = 0; i < 5 && i < BUFFER_SIZE; ++i) {
        std::cout << buffer.samples[i] << " ";
    }
    std::cout << "...\n";

    for (int i = 0; i < BUFFER_SIZE; ++i) {
        classificador.processarAmostra(static_cast<float>(buffer.samples[i]));
    }

    ecg_buffer_reset(&buffer);
}

}  // namespace

int main(int argc, char* argv[]) {
    const std::string port = (argc >= 2) ? argv[1] : "COM3";

    SerialPort serial(port, 115200);
    if (!serial.isOpen()) {
        std::cerr << "Uso: programa_ecg [PORTA]\n";
        std::cerr << "Exemplo: programa_ecg COM3\n";
        std::cerr << "Feche o Monitor/Plotter Serial do Arduino antes de executar.\n";
        return 1;
    }

    std::cout << "Lendo ESP32 em " << port << " @ 115200 baud...\n";
    std::cout << "Pressione Ctrl+C para encerrar.\n";
    std::cout << "Feche o Monitor Serial do Arduino IDE antes de executar.\n";
    std::cout.flush();

    ECG_Buffer buffer{};
    ecg_buffer_init(&buffer);
    ClassificadorECG classificador;

    std::string line;
    auto lastWarnTime = std::chrono::steady_clock::now();
    unsigned long totalSamples = 0;

    while (true) {
        if (!serial.readLine(line)) {
            const auto now = std::chrono::steady_clock::now();
            if (totalSamples == 0 &&
                std::chrono::duration_cast<std::chrono::seconds>(now - lastWarnTime).count() >= 3) {
                std::cout << "Aguardando dados do ESP32... Verifique COM, cabo USB e sketch "
                             "capture_signal.ino carregado.\n";
                std::cout.flush();
                lastWarnTime = now;
            }
            continue;
        }

        lastWarnTime = std::chrono::steady_clock::now();

        uint16_t sample = 0;
        if (!parseSample(line, sample)) {
            if (!line.empty()) {
                std::cout << "Linha ignorada (nao e numero): \"" << line << "\"\n";
                std::cout.flush();
            }
            continue;
        }

        ++totalSamples;
        if (totalSamples == 1) {
            std::cout << "Primeira amostra recebida: " << sample << "\n";
            std::cout.flush();
        }

        if (ecg_buffer_push(&buffer, sample)) {
            processFullBuffer(buffer, classificador);
            std::cout.flush();
        }
    }

    return 0;
}
