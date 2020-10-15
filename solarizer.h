#ifndef SOLARIZATOR_H
#define SOLARIZATOR_H
#include "utility.h"

class Solarizer {
public:
    Solarizer();

    bool _isOn = false;

    QImage solarize(const QImage& image);
};

#endif // SOLARIZATOR_H
