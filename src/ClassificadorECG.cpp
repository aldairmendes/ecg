#include "ClassificadorECG.h"
#include <iostream>
#include <vector>

ClassificadorECG::ClassificadorECG()
    : env(ORT_LOGGING_LEVEL_WARNING, "ecg"),
      session(env, "data/modelo_ecg.onnx", Ort::SessionOptions{}),
      ultimaClasse(-1) {
    buffer.index = 0;
    buffer.ready = false;
}

void ClassificadorECG::processarAmostra(float valorBruto) {
    buffer.samples[buffer.index] = normalizar(valorBruto);
    buffer.index++;

    if (buffer.index >= BUFFER_SIZE) {
        buffer.ready = true;
        buffer.index = 0;
        std::string resultado = classificar();
        buffer.ready = false;
    }
}

float ClassificadorECG::normalizar(float entrada) {
    // Dados do MIT-BIH já vêm normalizados (0.0 a 1.0): passa direto.
    // Quando vier do AD8232 real (ADC 12 bits, 0–4095), troque por:
    //     return entrada / 4095.0f;
    return entrada;
}

std::string ClassificadorECG::classificar() {
    try {
        std::vector<float> input(buffer.samples, buffer.samples + BUFFER_SIZE);
        std::vector<int64_t> shape = {1, BUFFER_SIZE};

        auto memory_info = Ort::MemoryInfo::CreateCpu(OrtArenaAllocator, OrtMemTypeDefault);
        Ort::Value input_tensor = Ort::Value::CreateTensor<float>(
            memory_info, input.data(), input.size(), shape.data(), shape.size()
        );

        const char* input_names[]  = {"float_input"};
        const char* output_names[] = {"output_label"};

        auto outputs = session.Run(
            Ort::RunOptions{nullptr},
            input_names, &input_tensor, 1,
            output_names, 1
        );

        ultimaClasse = outputs[0].GetTensorData<int64_t>()[0];

        switch (ultimaClasse) {
            case 0:  return "Normal";
            case 1:
            case 2:
            case 3:
            case 4:  return "Possivel Arritmia";
            default: return "Indefinido";
        }

    } catch (const Ort::Exception& e) {
        std::cerr << "Erro ONNX: " << e.what() << std::endl;
        ultimaClasse = -1;
        return "Erro";
    } catch (const std::exception& e) {
        std::cerr << "Erro: " << e.what() << std::endl;
        ultimaClasse = -1;
        return "Erro";
    }
}

int64_t ClassificadorECG::getUltimaClasse() const {
    return ultimaClasse;
}
