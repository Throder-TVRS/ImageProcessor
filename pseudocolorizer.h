#ifndef PSEUDOCOLORIZER_H
#define PSEUDOCOLORIZER_H
#include <QApplication>
#include <QString>
#include <QFileDialog>
#include <iostream>
#include "utility.h"

class PseudoColorizer {
public:
    PseudoColorizer();

    uint64_t _q1 = 0;
    uint64_t _q2 = 0;
    uint64_t _q3 = 0;
    bool _isOn = false;

    QImage pseudo_colorize(const QImage& image);
};

#endif // PSEUDOCOLORIZER_H
