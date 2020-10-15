#ifndef BINARIZATOR_H
#define BINARIZATOR_H
#include "utility.h"

class Binarizer {
public:
    Binarizer();

    bool _isOn = false;
    uint64_t _trashhold = 256;

    QImage binaryze(const QImage& image);
};

#endif // BINARIZATOR_H
