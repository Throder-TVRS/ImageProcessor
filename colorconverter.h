#ifndef COLORCONVERTER_H
#define COLORCONVERTER_H
#include <QApplication>
#include <QString>
#include <QFileDialog>
#include <iostream>
#include "utility.h"

enum MIXER_TYPE {
    RED,
    GREEN,
    BLUE
};

class ColorConverter {
public:
    ColorConverter();

    uint64_t _red_percentage = 33;
    uint64_t _green_percentage = 33;
    uint64_t _blue_percentage = 34;

    void change_mixing_proportion(MIXER_TYPE mixer_type, int mixer_value);
    QImage gray_scale_image(const QImage& image);
    QRgb normalize_color(int red, int green, int blue);
};

#endif // COLORCONVERTER_H
