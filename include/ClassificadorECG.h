#ifndef CLASSIFICADOR_ECG_H
#define CLASSIFICADOR_ECG_H

#include <string>
#include <vector>
#include "EcgBuffer.h"
#include <onnxruntime_cxx_api.h>

class ClassificadorECG {
private:
    ECG_Buffer buffer;
    Ort::Env env;
    Ort::Session session;
    int64_t ultimaClasse;

public:
    ClassificadorECG();
    void processarAmostra(float valorBruto);
    float normalizar(float entrada);
    std::string classificar();
    int64_t getUltimaClasse() const;
};

#endif
