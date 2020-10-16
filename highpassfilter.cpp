#include "highpassfilter.h"

HighPassFilter::HighPassFilter() {
    H1 = Filter(3, std::vector<int>(3));
    for(auto& x :H1)
        for(auto& y : x)
            y = -1;
    H1[1][1] = 9;

    H2 = H1;
    H2[0][0] = 0;
    H2[0][2] = 0;
    H2[2][0] = 0;
    H2[2][2] = 0;
    H2[1][1] = 5;

    H3 = H2;
    H3[0][0] = 1;
    H3[0][2] = 1;
    H3[2][0] = 1;
    H3[2][2] = 1;
    H3[0][1] = -2;
    H3[1][0] = -2;
    H3[2][1] = -2;
    H3[1][2] = -2;
}

uint64_t use_H(const HighPassFilter::Filter& H, const QImage& image, uint64_t x, uint64_t y) {
    int64_t sum = 0;
    for(uint64_t i = 0; i < H.size(); i++)
        for(uint64_t j = 0; j < H.size(); j++)
            sum += H[i][j] * image.pixelColor(x + i, y + j).red();
    sum = std::min(sum, int64_t(255));
    return std::max(int64_t(0), sum);
}

QImage HighPassFilter::apply_filter(const QImage &image, HighPassFilter::Filter H) {
    QImage exp_image = expand_image(image, 3);
    QImage new_image = QImage(image.size(), QImage::Format_RGB32);
    uint64_t color;
    for(uint64_t x = 0; x < uint64_t(exp_image.width() - H.size() + 1); x++)
        for(uint64_t y = 0; y < uint64_t(exp_image.height() - H.size() + 1); y++) {
            color = use_H(H, exp_image, x, y);
            new_image.setPixelColor(x, y, qRgb(color, color, color));
        }
    return new_image;
}
