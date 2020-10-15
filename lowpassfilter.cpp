#include "lowpassfilter.h"

LowPassFilter::LowPassFilter() {
    std::vector<std::vector<int>> vec(3, std::vector<int>(3));
    for(auto& x : vec)
        for(auto& y : x)
            y = 1;
    H1.matrix = vec;
    H1.denumerator = 9;
    vec[1][1] = 2;
    H2.matrix = vec;
    H2.denumerator = 10;
    vec[1][0] = 2;
    vec[0][1] = 2;
    vec[2][1] = 2;
    vec[1][2] = 2;
    vec[1][1] = 4;
    H3.matrix = vec;
    H3.denumerator = 16;
}

uint64_t use_H(const LowPassFilter::Filter& H, const QImage& image, uint64_t x, uint64_t y) {
    uint64_t sum = 0;
    for(uint64_t i = 0; i < H.matrix.size(); i++)
        for(uint64_t j = 0; j < H.matrix.size(); j++)
            sum += H.matrix[i][j] * image.pixelColor(x + i, y + j).red();
    return uint64_round(sum , H.denumerator, 127);
}

QImage LowPassFilter::apply_H(const QImage &image, Filter H) {
    QImage exp_image = expand_image(image, 3);
    QImage new_image = QImage(image.size(), QImage::Format_RGB32);
    uint64_t color;
    for(uint64_t x = 0; x < uint64_t(exp_image.width() - 1 - H.matrix.size() / 2); x++)
        for(uint64_t y = 0; y < uint64_t(exp_image.height() - 1 - H.matrix.size() / 2); y++) {
            color = use_H(H, exp_image, x, y);
            new_image.setPixelColor(x, y, qRgb(color, color, color));
        }
    return new_image;
}

