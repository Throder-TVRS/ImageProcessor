#ifndef GAMMANIZATOR_H
#define GAMMANIZATOR_H
#include "utility.h"

class Gammanizer {
public:
    Gammanizer();

    double gamma = 1.0;
    bool _isOn = false;

    QImage gammanize(const QImage& image);
};

#endif // GAMMANIZATOR_H
