#ifndef NEGATIVETRASHHOLD_H
#define NEGATIVETRASHHOLD_H
#include "utility.h"

class NegativeTrashhold {
public:
    NegativeTrashhold();

    bool _isOn = false;
    uint64_t _trashhold = 256;

    QImage negativize(const QImage& image);
};

#endif // NEGATIVETRASHHOLD_H
