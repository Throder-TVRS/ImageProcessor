#ifndef BRIGHTNESSCHANGER_H
#define BRIGHTNESSCHANGER_H
#include <QApplication>
#include <QImage>

class BrightnessChanger {
public:
    BrightnessChanger();

    int64_t _brightness_change = 0;
    bool _null_change = true;

    QImage change_brightness(const QImage& image);
};

#endif // BRIGHTNESSCHANGER_H
