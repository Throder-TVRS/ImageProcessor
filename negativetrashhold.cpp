#include "negativetrashhold.h"

NegativeTrashhold::NegativeTrashhold() {

}

QImage NegativeTrashhold::negativize(const QImage &image) {
    QImage new_image = QImage(image.size(), QImage::Format_RGB32);
    uint64_t color;
    for(uint64_t x = 0; x < image.width(); x++)
        for(uint64_t y = 0; y < image.height(); y++) {
            color = image.pixelColor(x, y).red();
            if(color < _trashhold)
                new_image.setPixel(x, y, qRgb(color, color, color));
            else
                new_image.setPixel(x, y, qRgb(255 - color,
                                              255 - color,
                                              255 - color));
        }
    return new_image;
}
