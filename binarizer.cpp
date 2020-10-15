#include "binarizer.h"

Binarizer::Binarizer() {

}

QImage Binarizer::binaryze(const QImage &image) {
    QImage new_image = QImage(image.size(), QImage::Format_RGB32);
    uint64_t color;
    for(uint64_t x = 0; x < uint64_t(image.width()); x++)
        for(uint64_t y = 0; y < uint64_t(image.height()); y++) {
            color = image.pixelColor(x, y).red();
            if(color < _trashhold)
                new_image.setPixel(x, y, qRgb(0, 0, 0));
            else
                new_image.setPixel(x, y, qRgb(255, 255, 255));
        }
    return new_image;
}
