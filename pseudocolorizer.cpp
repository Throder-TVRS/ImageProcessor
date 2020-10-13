#include "pseudocolorizer.h"

PseudoColorizer::PseudoColorizer() {

}

QImage PseudoColorizer::pseudo_colorize(const QImage &image) {
    if(!(_q1 < _q2) || !(_q2 < _q3))
        return image;
    uint64_t color;
    QImage new_image = QImage(image.size(), QImage::Format_RGB32);
    for(uint64_t x = 0; x < image.width(); x++) {
        for(uint64_t y = 0; y < image.height(); y++) {
            color = image.pixelColor(x, y).red();
            if(color < _q1)
                new_image.setPixel(x, y, qRgb(0, 0, 255));
            else if(_q1 <= color && color < _q2)
                new_image.setPixel(x, y, qRgb(0, 255, 0));
            else if(_q2 <= color && color < _q3)
                new_image.setPixel(x, y, qRgb(255, 255, 0));
            else
                new_image.setPixel(x, y, qRgb(255, 0, 0));
        }
    }
    return new_image;
}
