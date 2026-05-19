#ifndef ECG_BUFFER_H
#define ECG_BUFFER_H

#include <stdint.h>

#define BUFFER_SIZE 187

struct ECG_Buffer {
    uint16_t samples[BUFFER_SIZE];
    uint8_t index;
    bool ready;
};

void ecg_buffer_init(ECG_Buffer* buf);
bool ecg_buffer_push(ECG_Buffer* buf, uint16_t sample);
void ecg_buffer_reset(ECG_Buffer* buf);
bool ecg_buffer_is_ready(const ECG_Buffer* buf);

#endif
