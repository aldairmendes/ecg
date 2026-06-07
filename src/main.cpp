#include "ClassificadorECG.h"
#include "EcgBuffer.h"
#include "SerialPort.h"

#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <iomanip>
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

void saveBufferAsCsv(const ECG_Buffer& buffer, std::ofstream& output, int label) {
    output << std::scientific << std::setprecision(18);
    for (int i = 0; i < BUFFER_SIZE; ++i) {
        const double normalized = static_cast<double>(buffer.samples[i]) / 4095.0;
        output << normalized << ',';
    }
    output << label << '\n';
    output.flush();
}

static std::string quoteCommandArg(const std::string& arg) {
    std::string quoted = "\"";
    for (char c : arg) {
        if (c == '"') {
            quoted += "\\\"";
        } else {
            quoted += c;
        }
    }
    quoted += "\"";
    return quoted;
}

static std::FILE* openLivePlotProcess(const std::filesystem::path& scriptPath,
                                     double fs, double window, int interval) {
    const std::string command =
        "python -u " + quoteCommandArg(scriptPath.string()) +
        " --stdin --fs " + std::to_string(fs) +
        " --window " + std::to_string(window) +
        " --interval " + std::to_string(interval);
    std::cout << "Iniciando plot Python: " << command << "\n";
    return _popen(command.c_str(), "w");
}

static bool argEquals(const char* a, const char* b) {
    return std::strcmp(a, b) == 0;
}

static std::string getArgValue(int argc, char* argv[], int& i) {
    if (i + 1 < argc) {
        return argv[++i];
    }
    return std::string();
}

void processFullBuffer(ECG_Buffer& buffer, ClassificadorECG& classificador,
                       std::ofstream* csvOutput, int csvLabel) {
    std::cout << "Buffer cheio (" << BUFFER_SIZE << " amostras): ";
    for (int i = 0; i < BUFFER_SIZE; ++i) {
        std::cout << buffer.samples[i];
        if (i + 1 < BUFFER_SIZE) {
            std::cout << ' ';
        }
    }
    std::cout << "\n";

    if (csvOutput && csvOutput->is_open()) {
        saveBufferAsCsv(buffer, *csvOutput, csvLabel);
    }

    for (int i = 0; i < BUFFER_SIZE; ++i) {
        classificador.processarAmostra(static_cast<float>(buffer.samples[i]));
    }

    ecg_buffer_reset(&buffer);
}

}  // namespace

int main(int argc, char* argv[]) {
    const std::string port = (argc >= 2) ? argv[1] : "COM3";
    const std::string csvFile = (argc >= 3) ? argv[2] : "data\\dados.csv";

    bool enablePlot = false;
    std::string plotScript = "ecg\\live_plot.py";
    double plotWindow = 5.0;
    double plotFs = 250.0;
    int plotInterval = 40;
    int csvLabel = 0;

    for (int i = 3; i < argc; ++i) {
        if (argEquals(argv[i], "--plot")) {
            enablePlot = true;
        } else if (argEquals(argv[i], "--plot-script")) {
            plotScript = getArgValue(argc, argv, i);
        } else if (argEquals(argv[i], "--plot-window")) {
            plotWindow = std::atof(getArgValue(argc, argv, i).c_str());
        } else if (argEquals(argv[i], "--plot-fs")) {
            plotFs = std::atof(getArgValue(argc, argv, i).c_str());
        } else if (argEquals(argv[i], "--plot-interval")) {
            plotInterval = std::atoi(getArgValue(argc, argv, i).c_str());
        } else if (argEquals(argv[i], "--label")) {
            csvLabel = std::atoi(getArgValue(argc, argv, i).c_str());
        }
    }

    std::ofstream csvOutput;
    if (!csvFile.empty()) {
        const std::filesystem::path csvPath(csvFile);
        if (csvPath.has_parent_path()) {
            std::filesystem::create_directories(csvPath.parent_path());
        }
        csvOutput.open(csvFile, std::ios::app);
        if (!csvOutput.is_open()) {
            std::cerr << "Nao foi possivel abrir arquivo CSV: " << csvFile << "\n";
            return 1;
        }
        std::cout << "Gravando CSV em: " << std::filesystem::absolute(csvPath).string() << "\n";
    }

    SerialPort serial(port, 115200);
    if (!serial.isOpen()) {
        std::cerr << "Uso: programa_ecg [PORTA] [ARQUIVO_CSV_OPCIONAL] [--label N] [--plot] [--plot-script PATH] [--plot-window SEC] [--plot-fs FS] [--plot-interval MS]\n";
        std::cerr << "Exemplo: programa_ecg COM3 dados.csv --label 0 --plot --plot-script ecg\\live_plot.py --plot-window 5 --plot-fs 250\n";
        std::cerr << "Feche o Monitor/Plotter Serial do Arduino antes de executar.\n";
        return 1;
    }

    std::FILE* plotPipe = nullptr;
    if (enablePlot) {
        std::filesystem::path scriptPath(plotScript);
        if (scriptPath.is_relative()) {
            scriptPath = std::filesystem::current_path() / scriptPath;
        }
        if (!std::filesystem::exists(scriptPath)) {
            std::cerr << "Arquivo de plot nao encontrado: " << scriptPath.string() << "\n";
        } else {
            plotPipe = openLivePlotProcess(scriptPath, plotFs, plotWindow, plotInterval);
            if (!plotPipe) {
                std::cerr << "Falha ao iniciar plot Python. Verifique o Python e o script live_plot.py.\n";
            }
        }
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

        if (plotPipe) {
            std::fprintf(plotPipe, "%u\n", sample);
            std::fflush(plotPipe);
        }

        ++totalSamples;
        if (totalSamples == 1) {
            std::cout << "Primeira amostra recebida: " << sample << "\n";
            std::cout.flush();
        }

        if (ecg_buffer_push(&buffer, sample)) {
            processFullBuffer(buffer, classificador, csvOutput.is_open() ? &csvOutput : nullptr, csvLabel);
            std::cout.flush();
        }
    }

    return 0;
}
