#ifndef ECG_DATA_H
#define ECG_DATA_H

#include <stdint.h>

#define BUFFER_SIZE 187

struct ECG_Buffer {
    float samples[BUFFER_SIZE];
    uint16_t index;
    bool ready;
};

#endif