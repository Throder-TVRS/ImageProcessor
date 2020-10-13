#ifndef UTILITY_H
#define UTILITY_H
#include "mainwindow.h"
#include <algorithm>

uint64_t uint64_round(uint64_t a, uint64_t b, uint64_t lim);
QImage scale_image(const QImage& image, int width, int height);

#endif // UTILITY_H
