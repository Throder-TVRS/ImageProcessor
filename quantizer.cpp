#include "quantizer.h"

Quantizer::Quantizer() {

}

QImage Quantizer::quantize(const QImage &image) {
    QImage new_image = QImage(image.size(), QImage::Format_RGB32);
    uint64_t color;
    for(uint64_t x = 0; x < uint64_t(image.width()); x++)
        for(uint64_t y = 0; y < uint64_t(image.height()); y++) {
            color = image.pixelColor(x, y).red();
            color = (color / _quanta_amount) * _quanta_amount;
            new_image.setPixel(x, y, qRgb(color, color, color));
        }
    return new_image;
}
