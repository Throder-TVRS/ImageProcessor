#ifndef CONTRASTER_H
#define CONTRASTER_H
#include <QApplication>
#include <QImage>
#include "utility.h"
#include <algorithm>
#include <iostream>

class Contraster {
public:
    Contraster();

    bool _isOn = false;
    bool _decrease_mode = false;
    uint64_t _q1 = 0;
    uint64_t _q2 = 255;

    QImage change_contrast(const QImage& image);
};

#endif // CONTRASTER_H
