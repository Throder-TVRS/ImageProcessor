#include "contraster.h"

Contraster::Contraster() {

}

QImage Contraster::change_contrast(const QImage &image) {
    if(!_isOn)
        return image;
    QImage new_image = QImage(image.size(), QImage::Format_RGB32);
    uint64_t color;
    if(_decrease_mode) {
        for(uint64_t x = 0; x < uint64_t(image.width()); x++) {
            for(uint64_t y = 0; y < uint64_t(image.height()); y++) {
                color = image.pixelColor(x, y).red();
//                if(color < _q1 || _q1 >= _q2)
//                    color = 0;
//                else if(color > _q2)
//                    color = 255;
//                else
                    color = _q1 + uint64_round(color * (_q2 - _q1), 255, 127);
                new_image.setPixel(x, y, qRgb(color, color, color));
            }
        }
    }
    else {
        for(uint64_t x = 0; x < uint64_t(image.width()); x++) {
            for(uint64_t y = 0; y < uint64_t(image.height()); y++) {
                color = image.pixelColor(x, y).red();
                if(color < _q1 || _q1 >= _q2)
                    color = 0;
                else if(color > _q2)
                    color = 255;
                else
                    color = uint64_round((color - _q1) * 255, (_q2 - _q1), 127);
                new_image.setPixel(x, y, qRgb(color, color, color));
            }
        }
    }
    return new_image;
}
