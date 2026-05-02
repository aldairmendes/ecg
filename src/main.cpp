#include "ClassificadorECG.h"

int main() {
    ClassificadorECG meuClassificador;

    // Envia 500 amostras simuladas
    for (int i = 0; i < 500; i++) {
        meuClassificador.processarAmostra(1.23f); 
    }

    return 0;
}