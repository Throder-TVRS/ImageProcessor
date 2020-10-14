#ifndef BINARIZATOR_H
#define BINARIZATOR_H
#include <QApplication>
#include <QImage>

class Binarizator {
public:
    Binarizator();

    bool _isOn = false;
    uint64_t _trashhold = 0;

    QImage binaryze(const QImage& image);
};

#endif // BINARIZATOR_H
