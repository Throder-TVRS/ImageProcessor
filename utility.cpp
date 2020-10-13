#include "utility.h"

uint64_t uint64_round(uint64_t numenator, uint64_t denumenator, uint64_t lim) {
    if(numenator % denumenator > lim)
        numenator += denumenator - 1;
    return numenator /= denumenator;
}

QImage scale_image(const QImage& image, int width, int height) {
    QImage scaled_image;
    int image_width = image.width();
    int image_height = image.height();
    if(image_width > width)
        scaled_image = image.scaledToWidth(width);
    if(image_height > height)
        scaled_image = image.scaledToHeight(height);
    if(scaled_image.isNull())
        scaled_image = image;
    return scaled_image;
}
