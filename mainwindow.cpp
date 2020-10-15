#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QColorDialog>

MainWindow::MainWindow(QWidget *parent, ImageProcessor *processor)
    : QMainWindow(parent)
    , _processor(processor)
    , ui(new Ui::MainWindow) {

    ui->setupUi(this);
    ui->pseudo_first_color->setStyleSheet("background-color: blue");
    ui->pseudo_second_color->setStyleSheet("background-color: green");
    ui->pseudo_third_color->setStyleSheet("background-color: yellow");
    ui->pseudo_fourth_color->setStyleSheet("background-color: red");
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::update_image() {
    if(_processor->_filepath.isEmpty() ||
       _processor->source_status)
        return;
    if(_processor->_filtered_status)
        ui->preview_label->setPixmap(QPixmap::fromImage(_processor->_filtered_image));
    else
        ui->preview_label->setPixmap(QPixmap::fromImage(_processor->_processed_image));
    ui->hystogram_label->setPixmap(QPixmap::fromImage(_processor->_hystogram));
}

void MainWindow::update_image(const QImage& image) {
    if(_processor->_filepath.isEmpty() ||
      !_processor->source_status)
        return;
    if(image == _processor->_filtered_image) {
        std::cerr << "PREVIEW\n";
        ui->preview_label->setPixmap(QPixmap::fromImage(_processor->_filtered_image));
    }
    else if(image != _processor->_source_image) {
        QImage scaled_processed_image = scale_image(image, ui->preview_label->width(), ui->preview_label->height());
        ui->preview_label->setPixmap(QPixmap::fromImage(scaled_processed_image));
    }
    else
        ui->preview_label->setPixmap(QPixmap::fromImage(image));
}

void MainWindow::on_load_image_button_clicked() {
    QString new_filepath = QFileDialog::getOpenFileName(0, "File selection", "", "*.jpg *.png *.bmp");
    if(new_filepath.isEmpty() || _processor->_filepath == new_filepath)
        return;
    _processor->load_image(new_filepath);
    _processor->apply_transformations(Transformations::GRAY_SCALE, true);
    _processor->apply_transformations(Transformations::GRAY_SCALE, false);
    update_image();
}

void MainWindow::on_red_slider_valueChanged(int value) {
    _processor->_color_converter->change_mixing_proportion(MIXER_TYPE::RED, value);
    ui->red_slider_display->display(value);
    if(_processor->source_status)
        return;
    _processor->apply_transformations(Transformations::GRAY_SCALE, false);
    update_image();
}

void MainWindow::on_green_slider_valueChanged(int value) {
    _processor->_color_converter->change_mixing_proportion(MIXER_TYPE::GREEN, value);
    ui->green_slider_display->display(value);
    if(_processor->source_status)
        return;
    _processor->apply_transformations(Transformations::GRAY_SCALE, false);
    update_image();
}

void MainWindow::on_blue_slider_valueChanged(int value) {
    _processor->_color_converter->change_mixing_proportion(MIXER_TYPE::BLUE, value);
    ui->blue_slider_display->display(value);
    if(_processor->source_status)
        return;
    _processor->apply_transformations(Transformations::GRAY_SCALE, false);
    update_image();
}

void MainWindow::on_source_flag_box_stateChanged(int arg1) {
    if(arg1 == Qt::CheckState::Checked)
        _processor->source_status = true;
    if(arg1 == Qt::CheckState::Unchecked)
        _processor->source_status = false;
    if(_processor->source_status)
        update_image(_processor->_source_image);
    else if(!_processor->_filtered_status)
        _processor->apply_transformations(Transformations::GRAY_SCALE, false);
    update_image();
}

void MainWindow::on_reset_button_clicked() {
    _processor->_reset_mode = true;
    on_rgb_reset_clicked();
    on_gamma_reset_clicked();
    on_median_reset_clicked();
    on_pseudo_reset_clicked();
    on_lowpass_reset_clicked();
    on_contrast_reset_clicked();
    on_gaussian_reset_clicked();
    on_highpass_reset_clicked();
    on_bightness_reset_clicked();
    on_binarization_reset_clicked();
    on_quantization_reset_clicked();
    on_negative_trashhold_reset_clicked();
    ui->solarization_box->setCheckState(Qt::CheckState::Unchecked);
    _processor->_reset_mode = false;
    _processor->apply_transformations(Transformations::GRAY_SCALE, false);
    update_image();
}

void MainWindow::on_brightness_change_slider_valueChanged(int value) {
    _processor->_brightness_changer->_brightness_change = value;
    ui->brightness_changer_display->display(value);
    if(value == 0)
        _processor->_brightness_changer->_null_change = true;
    else
        _processor->_brightness_changer->_null_change = false;
    _processor->apply_transformations(Transformations::BRIGHTNESS_CHANGE, false);
    update_image();
}

void MainWindow::on_negative_trashhold_slider_valueChanged(int value) {
    _processor->_negative_trashhold->_trashhold = value;
    ui->negative_trashhold_display->display(value);
    _processor->apply_transformations(Transformations::TRASHHOLD_NEGATIVE, false);
    update_image();
}

void MainWindow::on_negative_trashhold_box_stateChanged(int arg1) {
    if(arg1 == Qt::CheckState::Checked)
        _processor->_negative_trashhold->_isOn = true;
    if(arg1 == Qt::CheckState::Unchecked)
        _processor->_negative_trashhold->_isOn = false;
    if(_processor->_negative_trashhold->_isOn)
        _processor->apply_transformations(Transformations::TRASHHOLD_NEGATIVE, false);
    else
        _processor->apply_transformations(Transformations::GRAY_SCALE, false);
    update_image();
}

void MainWindow::on_binarizetion_slider_valueChanged(int value) {
    _processor->_binorizer->_trashhold = value;
    ui->binarization_display->display(value);
    _processor->apply_transformations(Transformations::BINARIZATION, false);
    update_image();
}

void MainWindow::on_binarization_box_stateChanged(int arg1) {
    if(arg1 == Qt::CheckState::Checked)
        _processor->_binorizer->_isOn = true;
    if(arg1 == Qt::CheckState::Unchecked)
        _processor->_binorizer->_isOn = false;
    if(_processor->_binorizer->_isOn)
        _processor->apply_transformations(Transformations::BINARIZATION, false);
    else
        _processor->apply_transformations(Transformations::GRAY_SCALE, false);
    update_image();
}

void MainWindow::on_contrast_q1_slider_valueChanged(int value) {
    _processor->_contraster->_q1 = value;
    ui->contrast_q1_display->display(value);
    _processor->apply_transformations(Transformations::CONTRAST, false);
    update_image();
}

void MainWindow::on_contrast_q2_slider_valueChanged(int value) {
    _processor->_contraster->_q2 = value;
    ui->contrast_q2_display->display(value);
    _processor->apply_transformations(Transformations::CONTRAST, false);
    update_image();
}

void MainWindow::on_contrast_box_stateChanged(int arg1) {
    if(arg1 == Qt::CheckState::Checked)
        _processor->_contraster->_isOn = true;
    if(arg1 == Qt::CheckState::Unchecked)
        _processor->_contraster->_isOn = false;
    if(_processor->_contraster->_isOn)
        _processor->apply_transformations(Transformations::CONTRAST, false);
    else
        _processor->apply_transformations(Transformations::GRAY_SCALE, false);
    update_image();
}

void MainWindow::on_contrast_decreas_mode_box_stateChanged(int arg1) {
    if(arg1 == Qt::CheckState::Checked)
        _processor->_contraster->_decrease_mode = true;
    if(arg1 == Qt::CheckState::Unchecked)
        _processor->_contraster->_decrease_mode = false;
    _processor->apply_transformations(Transformations::CONTRAST, false);
    update_image();
}

void MainWindow::on_gamma_box_stateChanged(int arg1) {
    if(arg1 == Qt::CheckState::Checked)
        _processor->_gammanizer->_isOn = true;
    if(arg1 == Qt::CheckState::Unchecked)
        _processor->_gammanizer->_isOn = false;
    if(_processor->_gammanizer->_isOn)
        _processor->apply_transformations(Transformations::GAMMA, false);
    else
        _processor->apply_transformations(Transformations::GRAY_SCALE, false);
    update_image();
}

void MainWindow::on_pseudo_q1_slider_valueChanged(int value) {
    _processor->_pseudo_colorizer->_q1 = value;
    ui->pseudo_q1_display->display(value);
    _processor->apply_transformations(Transformations::PSEUDO_COLORIZATION, false);
    update_image();
}

void MainWindow::on_pseudo_q2_slider_valueChanged(int value){
    _processor->_pseudo_colorizer->_q2 = value;
    ui->pseudo_q2_display->display(value);
    _processor->apply_transformations(Transformations::PSEUDO_COLORIZATION, false);
    update_image();
}

void MainWindow::on_pseudo_q3_slider_valueChanged(int value){
    _processor->_pseudo_colorizer->_q3 = value;
    ui->pseudo_q3_display->display(value);
    _processor->apply_transformations(Transformations::PSEUDO_COLORIZATION, false);
    update_image();
}

void MainWindow::on_pseudo_box_stateChanged(int arg1) {
    if(arg1 == Qt::CheckState::Checked)
        _processor->_pseudo_colorizer->_isOn = true;
    if(arg1 == Qt::CheckState::Unchecked)
        _processor->_pseudo_colorizer->_isOn = false;
    if(_processor->_pseudo_colorizer->_isOn)
        _processor->apply_transformations(Transformations::PSEUDO_COLORIZATION, false);
    else
        _processor->apply_transformations(Transformations::GRAY_SCALE, false);
    update_image();
}

void MainWindow::on_gamma_box_2_valueChanged(double arg1) {
    _processor->_gammanizer->gamma = arg1;
    _processor->apply_transformations(Transformations::GAMMA, false);
    update_image();
}

void MainWindow::on_quantization_slider_valueChanged(int value) {
    _processor->_quantizer->_quanta_amount = uint64_t(std::pow(2, value));
    ui->quantation_display->display(int(std::pow(2, value)));
    _processor->apply_transformations(Transformations::QUANTATION, false);
    update_image();
}

void MainWindow::on_quantation_box_stateChanged(int arg1) {
    if(arg1 == Qt::CheckState::Checked)
        _processor->_quantizer->_isOn = true;
    if(arg1 == Qt::CheckState::Unchecked)
        _processor->_quantizer->_isOn = false;
    if(_processor->_quantizer->_isOn)
        _processor->apply_transformations(Transformations::QUANTATION, false);
    else
        _processor->apply_transformations(Transformations::GRAY_SCALE, false);
    update_image();
}

std::string get_color_string(const QColor& color) {
    std::string str = "background-color: rgb(";
    str += std::to_string(color.red());
    str += ", " + std::to_string(color.green());
    str += ", " + std::to_string(color.blue());
    str += ")";
    return str;
}

void MainWindow::on_pseudo_first_color_clicked() {
    QColorDialog dialog;
    if(!dialog.exec())
        return;
    QColor color = _processor->_pseudo_colorizer->color1 = dialog.selectedColor();
    ui->pseudo_first_color->setStyleSheet(get_color_string(color).c_str());
    _processor->apply_transformations(Transformations::PSEUDO_COLORIZATION, false);
    update_image();
}

void MainWindow::on_pseudo_second_color_clicked() {
    QColorDialog dialog;
    if(!dialog.exec())
        return;
    QColor color = _processor->_pseudo_colorizer->color2 = dialog.selectedColor();
    ui->pseudo_second_color->setStyleSheet(get_color_string(color).c_str());
    _processor->apply_transformations(Transformations::PSEUDO_COLORIZATION, false);
    update_image();
}

void MainWindow::on_pseudo_third_color_clicked() {
    QColorDialog dialog;
    if(!dialog.exec())
        return;
    QColor color = _processor->_pseudo_colorizer->color3 = dialog.selectedColor();
    ui->pseudo_third_color->setStyleSheet(get_color_string(color).c_str());
    _processor->apply_transformations(Transformations::PSEUDO_COLORIZATION, false);
    update_image();
}

void MainWindow::on_pseudo_fourth_color_clicked() {
    QColorDialog dialog;
    if(!dialog.exec())
        return;
    QColor color = _processor->_pseudo_colorizer->color4 = dialog.selectedColor();
    ui->pseudo_fourth_color->setStyleSheet(get_color_string(color).c_str());
    _processor->apply_transformations(Transformations::PSEUDO_COLORIZATION, false);
    update_image();
}

void MainWindow::on_solarization_box_stateChanged(int arg1) {
    if(arg1 == Qt::CheckState::Checked)
        _processor->_solarizer->_isOn = true;
    if(arg1 == Qt::CheckState::Unchecked)
        _processor->_solarizer->_isOn = false;
    if(_processor->_solarizer->_isOn)
        _processor->apply_transformations(Transformations::SOLARIZATION, false);
    else
        _processor->apply_transformations(Transformations::GRAY_SCALE, false);
    update_image();
}

void MainWindow::on_lowpass_h1_button_clicked() {
    if(_processor->_filepath.isEmpty() ||
       _processor->source_status)
        return;
    if(!_processor->_filtered_status) {
        _processor->_filtered_image = _processor->_processed_image;
        _processor->_filtered_status = true;
    }
    LowPassFilter::Filter filter = _processor->_lowpass_filter->H1;
    _processor->_filtered_image = _processor->_lowpass_filter->apply_filter(_processor->_filtered_image, filter);
    _processor->calculate_hystogram();
    _processor->filtering_queue.push_back(FilterToken());
    _processor->filtering_queue.back().transform = Token::LOWPASS;
    _processor->filtering_queue.back().param = 1;
    update_image();
}

void MainWindow::on_lowpass_h2_button_clicked() {
    if(_processor->_filepath.isEmpty() ||
       _processor->source_status)
        return;
    if(!_processor->_filtered_status) {
        _processor->_filtered_image = _processor->_processed_image;
        _processor->_filtered_status = true;
    }
    LowPassFilter::Filter filter = _processor->_lowpass_filter->H2;
    _processor->_filtered_image = _processor->_lowpass_filter->apply_filter(_processor->_filtered_image, filter);
    _processor->calculate_hystogram();
    _processor->filtering_queue.push_back(FilterToken());
    _processor->filtering_queue.back().transform = Token::LOWPASS;
    _processor->filtering_queue.back().param = 2;
    update_image();
}

void MainWindow::on_lowpass_h3_button_clicked() {
    if(_processor->_filepath.isEmpty() ||
       _processor->source_status)
        return;
    if(!_processor->_filtered_status) {
        _processor->_filtered_image = _processor->_processed_image;
        _processor->_filtered_status = true;
    }
    LowPassFilter::Filter filter = _processor->_lowpass_filter->H3;
    _processor->_filtered_image = _processor->_lowpass_filter->apply_filter(_processor->_filtered_image, filter);
    _processor->calculate_hystogram();
    _processor->filtering_queue.push_back(FilterToken());
    _processor->filtering_queue.back().transform = Token::LOWPASS;
    _processor->filtering_queue.back().param = 3;
    update_image();
}

void MainWindow::on_lowpass_reset_clicked() {
    if(_processor->_filepath.isEmpty() ||
       _processor->source_status)
        return;
    _processor->_filtered_status = false;
    _processor->calculate_hystogram();
    _processor->filtering_queue.clear();
    update_image();
}

void MainWindow::on_highpass_h1_button_clicked() {
    if(_processor->_filepath.isEmpty() ||
       _processor->source_status)
        return;
    if(!_processor->_filtered_status) {
        _processor->_filtered_image = _processor->_processed_image;
        _processor->_filtered_status = true;
    }
    HighPassFilter::Filter filter = _processor->_highpass_filter->H1;
    _processor->_filtered_image = _processor->_highpass_filter->apply_filter(_processor->_filtered_image, filter);
    _processor->calculate_hystogram();
    _processor->filtering_queue.push_back(FilterToken());
    _processor->filtering_queue.back().transform = Token::HIGHPASS;
    _processor->filtering_queue.back().param = 1;
    update_image();
}

void MainWindow::on_highpass_h2_button_clicked() {
    if(_processor->_filepath.isEmpty() ||
       _processor->source_status)
        return;
    if(!_processor->_filtered_status) {
        _processor->_filtered_image = _processor->_processed_image;
        _processor->_filtered_status = true;
    }
    HighPassFilter::Filter filter = _processor->_highpass_filter->H2;
    _processor->_filtered_image = _processor->_highpass_filter->apply_filter(_processor->_filtered_image, filter);
    _processor->calculate_hystogram();
    _processor->filtering_queue.push_back(FilterToken());
    _processor->filtering_queue.back().transform = Token::HIGHPASS;
    _processor->filtering_queue.back().param = 2;
    update_image();
}

void MainWindow::on_highpass_h3_button_clicked() {
    if(_processor->_filepath.isEmpty() ||
       _processor->source_status)
        return;
    if(!_processor->_filtered_status) {
        _processor->_filtered_image = _processor->_processed_image;
        _processor->_filtered_status = true;
    }
    HighPassFilter::Filter filter = _processor->_highpass_filter->H3;
    _processor->_filtered_image = _processor->_highpass_filter->apply_filter(_processor->_filtered_image, filter);
    _processor->calculate_hystogram();
    _processor->filtering_queue.push_back(FilterToken());
    _processor->filtering_queue.back().transform = Token::HIGHPASS;
    _processor->filtering_queue.back().param = 3;
    update_image();
}

void MainWindow::on_highpass_reset_clicked() {
    if(_processor->_filepath.isEmpty() ||
       _processor->source_status)
        return;
    _processor->_filtered_status = false;
    _processor->calculate_hystogram();
    _processor->filtering_queue.clear();
    update_image();
}

void MainWindow::on_mdian_use_button_clicked() {
    if(_processor->_filepath.isEmpty() ||
       _processor->source_status)
        return;
    if(!_processor->_filtered_status) {
        _processor->_filtered_image = _processor->_processed_image;
        _processor->_filtered_status = true;
    }
    _processor->_filtered_image = _processor->_median_filter->apply_filter(_processor->_filtered_image);
    _processor->calculate_hystogram();
    _processor->filtering_queue.push_back(FilterToken());
    _processor->filtering_queue.back().transform = Token::MEDIAN;
    _processor->filtering_queue.back().param = _processor->_median_filter->filter_size;
    update_image();
}

void MainWindow::on_median_size_box_valueChanged(int arg1) {
    _processor->_median_filter->filter_size = arg1;
}

void MainWindow::on_median_reset_clicked() {
    if(_processor->_filepath.isEmpty() ||
       _processor->source_status)
        return;
    _processor->_filtered_status = false;
    ui->median_size_box->setValue(3);
    _processor->calculate_hystogram();
    _processor->filtering_queue.clear();
    update_image();
}

void MainWindow::on_gaussian_use_button_clicked() {
    if(_processor->_filepath.isEmpty() ||
       _processor->source_status)
        return;
    if(!_processor->_filtered_status) {
        _processor->_filtered_image = _processor->_processed_image;
        _processor->_filtered_status = true;
    }
    _processor->_filtered_image = _processor->_gaussian_filter->apply_filter(_processor->_filtered_image);
    _processor->calculate_hystogram();
    _processor->filtering_queue.push_back(FilterToken());
    _processor->filtering_queue.back().transform = Token::GAUSSIAN;
    _processor->filtering_queue.back().param = _processor->_median_filter->filter_size;
    update_image();
}

void MainWindow::on_gaussian_reset_clicked() {
    if(_processor->_filepath.isEmpty() ||
       _processor->source_status)
        return;
    _processor->_filtered_status = false;
    ui->gaussian_size_box->setValue(3);
    _processor->calculate_hystogram();
    _processor->filtering_queue.clear();
    update_image();
}

void MainWindow::on_gaussian_size_box_valueChanged(int arg1) {
    _processor->_gaussian_filter->filter_size = arg1;
}

void MainWindow::on_rgb_reset_clicked() {
    _processor->_color_converter->_red_percentage = 30;
    _processor->_color_converter->_green_percentage = 59;
    _processor->_color_converter->_blue_percentage = 11;
    ui->red_slider->setValue(30);
    ui->green_slider->setValue(59);
    ui->blue_slider->setValue(11);
    ui->red_slider_display->display(30);
    ui->green_slider_display->display(59);
    ui->blue_slider_display->display(11);
    if(!_processor->_reset_mode) {
        _processor->apply_transformations(Transformations::GRAY_SCALE, false);
        update_image();
    }
}

void MainWindow::on_bightness_reset_clicked() {
    _processor->_brightness_changer->_brightness_change = 0;
    _processor->_brightness_changer->_null_change = true;
    ui->brightness_change_slider->setValue(0);
    ui->brightness_changer_display->display(0);
    if(!_processor->_reset_mode) {
        _processor->apply_transformations(Transformations::GRAY_SCALE, false);
        update_image();
    }
}

void MainWindow::on_binarization_reset_clicked() {
    _processor->_binorizer->_isOn = false;
    _processor->_binorizer->_trashhold = 256;
    ui->binarization_box->setCheckState(Qt::CheckState::Unchecked);
    ui->binarizetion_slider->setValue(256);
    ui->binarization_display->display(256);
    if(!_processor->_reset_mode) {
        _processor->apply_transformations(Transformations::BINARIZATION, false);
        update_image();
    }
}

void MainWindow::on_negative_trashhold_reset_clicked() {
    _processor->_negative_trashhold->_isOn = false;
    _processor->_negative_trashhold->_trashhold = 256;
    ui->negative_trashhold_box->setCheckState(Qt::CheckState::Unchecked);
    ui->negative_trashhold_slider->setValue(256);
    ui->negative_trashhold_display->display(256);
    if(!_processor->_reset_mode) {
        _processor->apply_transformations(Transformations::TRASHHOLD_NEGATIVE, false);
        update_image();
    }
}

void MainWindow::on_contrast_reset_clicked() {
    _processor->_contraster->_isOn = false;
    ui->contrast_box->setCheckState(Qt::CheckState::Unchecked);
    ui->contrast_decreas_mode_box->setCheckState(Qt::CheckState::Unchecked);
    ui->contrast_q1_display->display(0);
    ui->contrast_q2_display->display(255);
    ui->contrast_q1_slider->setValue(0);
    ui->contrast_q2_slider->setValue(255);
    if(!_processor->_reset_mode) {
        _processor->apply_transformations(Transformations::CONTRAST, false);
        update_image();
    }
}

void MainWindow::on_gamma_reset_clicked() {
    _processor->_gammanizer->_isOn = false;
    _processor->_gammanizer->gamma = 1;
    ui->gamma_box->setCheckState(Qt::CheckState::Unchecked);
    ui->gamma_box_2->setValue(1);
    if(!_processor->_reset_mode) {
        _processor->apply_transformations(Transformations::GAMMA, false);
        update_image();
    }
}

void MainWindow::on_quantization_reset_clicked() {
    _processor->_quantizer->_isOn = false;
    _processor->_quantizer->_quanta_amount = 1;
    ui->quantation_box->setCheckState(Qt::CheckState::Unchecked);
    ui->quantization_slider->setValue(0);
    ui->quantation_display->display(1);
    if(!_processor->_reset_mode) {
        _processor->apply_transformations(Transformations::QUANTATION, false);
        update_image();
    }
}

void MainWindow::on_pseudo_reset_clicked() {
    _processor->_pseudo_colorizer->_isOn = false;
    _processor->_pseudo_colorizer->_q1 = 50;
    _processor->_pseudo_colorizer->_q2 = 127;
    _processor->_pseudo_colorizer->_q3 = 200;
    _processor->_pseudo_colorizer->color1 = qRgb(0, 0, 255);
    _processor->_pseudo_colorizer->color2 = qRgb(255, 255, 0);
    _processor->_pseudo_colorizer->color3 = qRgb(0, 255, 0);
    _processor->_pseudo_colorizer->color4 = qRgb(255, 0, 0);
    ui->pseudo_first_color->setStyleSheet("background-color: blue");
    ui->pseudo_second_color->setStyleSheet("background-color: green");
    ui->pseudo_third_color->setStyleSheet("background-color: yellow");
    ui->pseudo_fourth_color->setStyleSheet("background-color: red");
    ui->pseudo_q1_display->display(50);
    ui->pseudo_q2_display->display(127);
    ui->pseudo_q3_display->display(200);
    ui->pseudo_q1_slider->setValue(50);
    ui->pseudo_q2_slider->setValue(127);
    ui->pseudo_q3_slider->setValue(200);
    ui->pseudo_box->setCheckState(Qt::CheckState::Unchecked);
    if(!_processor->_reset_mode) {
        _processor->apply_transformations(Transformations::PSEUDO_COLORIZATION, false);
        update_image();
    }
}

void MainWindow::on_save_image_button_clicked() {
    _processor->save_image();
}
