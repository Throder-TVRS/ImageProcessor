#include "gammanizator.h"

Gammanizator::Gammanizator() {

}

QImage Gammanizator::gammanize(const QImage &image) {
    if(!_isOn)
        return image;
    QImage new_image = QImage(image.size(), QImage::Format_RGB32);
    uint64_t color;
    for(uint64_t x = 0; x < image.width(); x++) {
        for(uint64_t y = 0; y < image.height(); y++) {
            color = image.pixelColor(x, y).red();
            color = uint64_t(255 * std::pow((double(color) / double(255)), gamma));
            new_image.setPixel(x, y, qRgb(color, color, color));
        }
    }
    return new_image;
}
