#include "brightnesschanger.h"

BrightnessChanger::BrightnessChanger() {

}

QImage BrightnessChanger::change_brightness(const QImage& image) {
    if(_null_change)
        return image;
    QImage new_image(image.size(), QImage::Format_RGB32);
    int64_t color;
    for(uint64_t x = 0; x < image.width(); x++)
        for(uint64_t y = 0; y < image.height(); y++) {
            color = int64_t(image.pixelColor(x, y).red()) + _brightness_change;
            if(color < 0)
                new_image.setPixel(x, y, qRgb(0, 0, 0));
            else if(color > 255)
                new_image.setPixel(x, y, qRgb(255, 255, 255));
            else
                new_image.setPixel(x, y, qRgb(color, color, color));
        }
    return new_image;
}
