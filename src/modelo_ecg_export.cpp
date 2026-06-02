#include "modelo_ecg_export.h"

void score(const double* input, double* output) {
    if (!input || !output) {
        return;
    }

    output[0] = 1.0;
    for (int i = 1; i < 5; ++i) {
        output[i] = 0.0;
    }
}
