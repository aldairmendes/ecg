#include "EcgBuffer.h"

void ecg_buffer_init(ECG_Buffer* buf) {
    buf->index = 0;
    buf->ready = false;
}

bool ecg_buffer_push(ECG_Buffer* buf, uint16_t sample) {
    if (buf->ready) {
        return false;
    }

    buf->samples[buf->index++] = sample;

    if (buf->index >= BUFFER_SIZE) {
        buf->ready = true;
        return true;
    }

    return false;
}

void ecg_buffer_reset(ECG_Buffer* buf) {
    buf->index = 0;
    buf->ready = false;
}

bool ecg_buffer_is_ready(const ECG_Buffer* buf) {
    return buf->ready;
}
