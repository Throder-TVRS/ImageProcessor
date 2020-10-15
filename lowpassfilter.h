#ifndef LOWPASSFILTER_H
#define LOWPASSFILTER_H
#include "utility.h"

class LowPassFilter {
public:
    LowPassFilter();

    struct Filter {
        std::vector<std::vector<int>> matrix;
        int denumerator;
    };

    Filter H1;
    Filter H2;
    Filter H3;

    QImage apply_H(const QImage& image, Filter H);

};

#endif // LOWPASSFILTER_H
