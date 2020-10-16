#include "solarizer.h"

Solarizer::Solarizer() {

}

QImage Solarizer::solarize(const QImage &image) {
    QImage new_image = QImage(image.size(), QImage::Format_RGB32);
    uint64_t color;
    double a = -255.0 / (128.0 * 127.0);
    double b = -255.0 * a;
    for(uint64_t x = 0; x < uint64_t(image.width()); x++)
        for(uint64_t y = 0; y < uint64_t(image.height()); y++) {
            color = image.pixelColor(x, y).red();
            color = uint64_t(color * (color * a + b));
            color = std::min(color, uint64_t(255));
            new_image.setPixel(x, y, qRgb(color, color, color));
        }
    return new_image;
}
