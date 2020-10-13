#include "mainwindow.h"
#include "imageprocessor.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    ColorConverter converter;
    BrightnessChanger brightness_changer;
    NegativeTrashhold negative_trashhold;
    Binarizator binarizator;
    Contraster contraster;
    Gammanizator gammanizator;
    PseudoColorizer pseudo_colorizer;
    ImageProcessor processor(&converter,
                             &brightness_changer,
                             &negative_trashhold,
                             &binarizator,
                             &contraster,
                             &gammanizator,
                             &pseudo_colorizer);
    MainWindow w(nullptr, &processor);
    w.setFixedSize(w.size());
    w.setWindowTitle("Image processor");
    w.show();
    return a.exec();
}
