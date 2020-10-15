#ifndef PSEUDOCOLORIZER_H
#define PSEUDOCOLORIZER_H
#include "utility.h"

class PseudoColorizer {
public:
    PseudoColorizer();

    uint64_t _q1 = 50;
    uint64_t _q2 = 127;
    uint64_t _q3 = 200;
    QColor color1 = qRgb(0, 0, 255);
    QColor color2 = qRgb(255, 255, 0);
    QColor color3 = qRgb(0, 255, 0);
    QColor color4 = qRgb(255, 0, 0);
    bool _isOn = false;

    QImage pseudo_colorize(const QImage& image);
};

#endif // PSEUDOCOLORIZER_H
