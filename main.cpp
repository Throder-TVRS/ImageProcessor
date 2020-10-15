#include "mainwindow.h"
#include "imageprocessor.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    ColorConverter converter;
    BrightnessChanger brightness_changer;
    NegativeTrashhold negative_trashhold;
    Binarizer binarizator;
    Contraster contraster;
    Gammanizer gammanizator;
    PseudoColorizer pseudo_colorizer;
    Solarizer solarizer;
    Quantizer quantizer;
    LowPassFilter lowpass_filter;
    HighPassFilter highpass_filter;
    MedianFilter median_filter;
    GaussianFilter gaussian_filter;
    ImageProcessor processor(&converter,
                             &brightness_changer,
                             &negative_trashhold,
                             &binarizator,
                             &contraster,
                             &gammanizator,
                             &pseudo_colorizer,
                             &solarizer,
                             &quantizer,
                             &lowpass_filter,
                             &highpass_filter,
                             &median_filter,
                             &gaussian_filter);
    MainWindow w(nullptr, &processor);
    w.setFixedSize(w.size());
    w.setWindowTitle("Image processor");
    w.show();
    return a.exec();
}
