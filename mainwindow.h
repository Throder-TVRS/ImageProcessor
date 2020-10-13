#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDialog>
#include <QPushButton>
#include <QPainter>
#include "imageprocessor.h"
class ImageProcessor;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT
private:
    ImageProcessor *_processor;

public:
    MainWindow(QWidget *parent = nullptr, ImageProcessor *processor = nullptr);
    ~MainWindow();

    void update_image();
    void update_image(const QImage& image);
private slots:
    void on_load_image_button_clicked();
    void on_red_slider_valueChanged(int value);
    void on_green_slider_valueChanged(int value);
    void on_blue_slider_valueChanged(int value);
    void on_source_flag_box_stateChanged(int arg1);
    void on_reset_button_clicked();
    void on_brightness_change_slider_valueChanged(int value);
    void on_negative_trashhold_slider_valueChanged(int value);
    void on_negative_trashhold_box_stateChanged(int arg1);
    void on_binarizetion_slider_valueChanged(int value);
    void on_binarization_box_stateChanged(int arg1);
    void on_contrast_q1_slider_valueChanged(int value);
    void on_contrast_q2_slider_valueChanged(int value);
    void on_contrast_box_stateChanged(int arg1);
    void on_contrast_decreas_mode_box_stateChanged(int arg1);
    void on_gamma_box_stateChanged(int arg1);
    void on_pseudo_q1_slider_valueChanged(int value);
    void on_pseudo_q2_slider_valueChanged(int value);
    void on_pseudo_q3_slider_valueChanged(int value);
    void on_pseudo_box_stateChanged(int arg1);
    void on_gamma_box_2_valueChanged(double arg1);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
