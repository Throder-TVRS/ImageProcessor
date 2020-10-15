#include "pseudocolorizer.h"

PseudoColorizer::PseudoColorizer() {

}

QImage PseudoColorizer::pseudo_colorize(const QImage &image) {
    if(!(_q1 < _q2) || !(_q2 < _q3))
        return image;
    uint64_t color;
    QImage new_image = QImage(image.size(), QImage::Format_RGB32);
    for(uint64_t x = 0; x < uint64_t(image.width()); x++) {
        for(uint64_t y = 0; y < uint64_t(image.height()); y++) {
            color = image.pixelColor(x, y).red();
            if(color < _q1)
                new_image.setPixelColor(x, y, color1);
            else if(_q1 <= color && color < _q2)
                new_image.setPixelColor(x, y, color2);
            else if(_q2 <= color && color < _q3)
                new_image.setPixelColor(x, y, color3);
            else
                new_image.setPixelColor(x, y, color4);
        }
    }
    return new_image;
}
