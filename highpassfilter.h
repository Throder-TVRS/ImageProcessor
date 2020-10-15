#ifndef HIGHPASSFILTER_H
#define HIGHPASSFILTER_H
#include "utility.h"

class HighPassFilter {
public:
    HighPassFilter();

    typedef std::vector<std::vector<int>> Filter;

    Filter H1;
    Filter H2;
    Filter H3;

    QImage apply_filter(const QImage& image, Filter H);
};

#endif // HIGHPASSFILTER_H
