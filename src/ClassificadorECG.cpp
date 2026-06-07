#include "ClassificadorECG.h"
#include <iostream>

// O modelo espera floats normalizados em [0.0, 1.0].
// O ADC do ESP32 produz inteiros em [0, 4095] (12 bits).
// O dataset MIT-BIH já vem normalizado, então ao rodar simulation.cpp os
// valores passam direto. Na captura real do AD8232, a divisão por 4095
// é feita antes de chegar aqui (em main.cpp, via saveBufferAsCsv /
// processFullBuffer). Se quiser centralizar, ative a linha abaixo em
// normalizar() e remova a divisão de main.cpp.

ClassificadorECG::ClassificadorECG()
    : env(ORT_LOGGING_LEVEL_WARNING, "ecg"),
      session(env, "data/modelo_ecg.onnx", Ort::SessionOptions{}),
      ultimaClasse(-1)
{}

// ─── Normalização ──────────────────────────────────────────────────────────

float ClassificadorECG::normalizar(float entrada) {
    // Dados do MIT-BIH já estão em [0,1]: passam direto.
    // Dados brutos do AD8232 (0-4095) são normalizados em main.cpp antes
    // de chegar aqui, então não precisamos dividir novamente.
    return entrada;
}

// ─── Acumulação de amostras ────────────────────────────────────────────────

void ClassificadorECG::processarAmostra(float valorBruto) {
    janelaSinal.push_back(normalizar(valorBruto));

    if (janelaSinal.size() >= TAMANHO_JANELA) {
        std::string resultado = classificarJanela();
        std::cout << "Classificacao: " << resultado << std::endl;
        std::cout.flush();
        janelaSinal.clear();
    }
}

// ─── Inferência ONNX ───────────────────────────────────────────────────────

int ClassificadorECG::classificar(const std::vector<float>& sinal) {
    try {
        // Copia para garantir que o buffer é contíguo e não-const
        std::vector<float> entrada(sinal.begin(), sinal.end());
        std::vector<int64_t> shape = {1, static_cast<int64_t>(entrada.size())};

        auto mem = Ort::MemoryInfo::CreateCpu(OrtArenaAllocator, OrtMemTypeDefault);
        Ort::Value tensor = Ort::Value::CreateTensor<float>(
            mem, entrada.data(), entrada.size(), shape.data(), shape.size()
        );

        const char* input_names[]  = {"float_input"};
        const char* output_names[] = {"output_label"};

        auto outputs = session.Run(
            Ort::RunOptions{nullptr},
            input_names, &tensor, 1,
            output_names, 1
        );

        ultimaClasse = outputs[0].GetTensorData<int64_t>()[0];
        return static_cast<int>(ultimaClasse);

    } catch (const Ort::Exception& e) {
        std::cerr << "Erro ONNX: " << e.what() << std::endl;
        ultimaClasse = -1;
        return -1;
    } catch (const std::exception& e) {
        std::cerr << "Erro: " << e.what() << std::endl;
        ultimaClasse = -1;
        return -1;
    }
}

// ─── Classificação ───────────────────────────────────────

std::string ClassificadorECG::classificarJanela() {
    static const char* nomes[] = {
        "Normal",
        "Arritmia supraventricular",
        "Batimento ventricular",
        "Fusao de batimentos",
        "Batimento desconhecido"
    };

    int cls = classificar(janelaSinal);
    if (cls >= 0 && cls < 5) {
        return nomes[cls];
    }
    return "Erro na inferencia";
}

int64_t ClassificadorECG::getUltimaClasse() const {
    return ultimaClasse;
}