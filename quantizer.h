#ifndef QUANTIZER_H
#define QUANTIZER_H
#include "utility.h"

class Quantizer {
public:
    Quantizer();

    uint64_t _quanta_amount = 1;
    bool _isOn = false;

    QImage quantize(const QImage& image);
};

#endif // QUANTIZER_H
