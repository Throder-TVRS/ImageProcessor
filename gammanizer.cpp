#include "gammanizer.h"

Gammanizer::Gammanizer() {

}

QImage Gammanizer::gammanize(const QImage &image) {
    QImage new_image = QImage(image.size(), QImage::Format_RGB32);
    uint64_t color;
    for(uint64_t x = 0; x < uint64_t(image.width()); x++) {
        for(uint64_t y = 0; y < uint64_t(image.height()); y++) {
            color = image.pixelColor(x, y).red();
            color = uint64_t(255 * std::pow((double(color) / double(255)), gamma));
            new_image.setPixel(x, y, qRgb(color, color, color));
        }
    }
    return new_image;
}
