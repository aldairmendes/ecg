#ifndef ECG_DATA_H
#define ECG_DATA_H

#include <stdint.h>

#define BUFFER_SIZE 188

// Utilizaremos o tipo uint16_t para guardar os sinais (variam de 0 a 4094) e o tipo uint8_t para indexar, 
// isso evita desperdício de memória.

// uint8_t: 0 a 2^8 - 1 (255).
// uint16_t: 0 a 2^16 - 1 (65.535).

struct ECG_Buffer {
    uint16_t samples[BUFFER_SIZE];
    uint8_t index;
    bool ready; // Indica que o buffer encheu
};

#endif