#ifndef GAMMANIZATOR_H
#define GAMMANIZATOR_H
#include <QApplication>
#include <QImage>
#include "utility.h"
#include <algorithm>
#include <iostream>
#include <cmath>

class Gammanizator {
public:
    Gammanizator();

    double gamma = 1.0;
    bool _isOn = false;

    QImage gammanize(const QImage& image);
};

#endif // GAMMANIZATOR_H
