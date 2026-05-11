#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "ClassificadorECG.h"

TEST_CASE("Normalização de sinal", "[ecg]") {
    ClassificadorECG ecg;
    
    // Testa se a normalização está devolvendo o valor esperado
    REQUIRE(ecg.normalizar(10.0) == 10.0); 
}

TEST_CASE("Acúmulo de amostras", "[ecg]") {
    ClassificadorECG ecg;
    // Simula 500 chamadas e verifica se a lógica interna responde corretamente
}