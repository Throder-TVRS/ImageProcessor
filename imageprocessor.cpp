#include "imageprocessor.h"

ImageProcessor::ImageProcessor(ColorConverter *color_converter,
                               BrightnessChanger *brightness_changer,
                               NegativeTrashhold *negative_trashhold,
                               Binarizer *binarizator,
                               Contraster *contraster,
                               Gammanizer *gammanizator,
                               PseudoColorizer *pseudo_colorizer,
                               Solarizer *solarizator,
                               Quantizer *quantizer,
                               LowPassFilter *lowpass_filter,
                               HighPassFilter *highpass_filter,
                               MedianFilter *median_filter,
                               GaussianFilter *gaussian_filter)
    : _color_converter(color_converter)
    , _brightness_changer(brightness_changer)
    , _negative_trashhold(negative_trashhold)
    , _binorizer(binarizator)
    , _contraster(contraster)
    , _gammanizer(gammanizator)
    , _quantizer(quantizer)
    , _pseudo_colorizer(pseudo_colorizer)
    , _solarizer(solarizator)
    , _lowpass_filter(lowpass_filter)
    , _highpass_filter(highpass_filter)
    , _median_filter(median_filter)
    , _gaussian_filter(gaussian_filter) {

    _hystogram = QImage(256, 280, QImage::Format_RGB32);
    _transformations_amount = 20;
    processing_list.resize(_transformations_amount);
    processing_status.resize(_transformations_amount);
    processing_status[0] = true;
}

void ImageProcessor::load_image(const QString& filepath) {
    _filepath = filepath;
    _default_size_source_image = _source_image = _processed_image = QImage(_filepath);
    _source_image = scale_image(_source_image, _preview_label_size, _preview_label_size);
}

void ImageProcessor::save_image() {
    QString fileName = QFileDialog::getSaveFileName();
    if (fileName.isEmpty())
        return;
    QImage buf = _color_converter->gray_scale_image(_default_size_source_image);
    QImage buf2 = _color_converter->gray_scale_image(_default_size_source_image);
    if(!_brightness_changer->_null_change)
        buf = _brightness_changer->change_brightness(buf);
    if(_negative_trashhold->_isOn)
        buf = _negative_trashhold->negativize(buf);
    if(_contraster->_isOn)
        buf = _contraster->change_contrast(buf);
    if(_gammanizer->_isOn)
        buf = _gammanizer->gammanize(buf);
    if(_binorizer->_isOn)
        buf = _binorizer->binaryze(buf);
    if(_quantizer->_isOn)
        buf = _quantizer->quantize(buf);
    if(_solarizer->_isOn)
        buf = _solarizer->solarize(buf);
    if(_pseudo_colorizer->_isOn)
        buf = _pseudo_colorizer->pseudo_colorize(buf);
    uint64_t median_size = _median_filter->filter_size;
    uint64_t gaussian_size = _gaussian_filter->filter_size;
    for(uint64_t i = 0; i < filtering_queue.size(); i++) {
        switch(filtering_queue[i].transform) {
            case LOWPASS:
                if(filtering_queue[i].param == 1)
                   buf = _lowpass_filter->apply_filter(buf, _lowpass_filter->H1);
                else if(filtering_queue[i].param == 2)
                    buf = _lowpass_filter->apply_filter(buf, _lowpass_filter->H2);
                else
                    buf = _lowpass_filter->apply_filter(buf, _lowpass_filter->H3);
                break;
            case HIGHPASS:
                if(filtering_queue[i].param == 1)
                   buf = _highpass_filter->apply_filter(buf, _highpass_filter->H1);
                else if(filtering_queue[i].param == 2)
                    buf = _highpass_filter->apply_filter(buf, _highpass_filter->H2);
                else
                    buf = _highpass_filter->apply_filter(buf, _highpass_filter->H3);
                break;
            case MEDIAN:
                _median_filter->filter_size = filtering_queue[i].param;
                buf = _median_filter->apply_filter(buf);
                break;
            case GAUSSIAN:
                _gaussian_filter->filter_size = filtering_queue[i].param;
                buf = _gaussian_filter->apply_filter(buf);
                break;
        }
    }
    _median_filter->filter_size = median_size;
    _gaussian_filter->filter_size = gaussian_size;
    buf.save(fileName);
}

void ImageProcessor::calculate_hystogram() {
    uint64_t h_max = 0, k;
    std::vector<uint64_t> h(256, 0);
    if(!_filtered_status) {
        for(int y = 0; y < _processed_image.height(); y++) {
            for(int x = 0; x < _processed_image.width(); x++) {
                k = _processed_image.pixelColor(x, y).red();
                h[k]++;
            }
        }
    }
    else {
        for(int y = 0; y < _filtered_image.height(); y++) {
            for(int x = 0; x < _filtered_image.width(); x++) {
                k = _filtered_image.pixelColor(x, y).red();
                h[k]++;
            }
        }
    }

    for(const auto& x : h)
        h_max = std::max(h_max, x);
    for(auto& x : h) {
        x *= 280;
        x += h_max - 1;
        x /= h_max;
    }
    for(uint64_t x = 0; x < 256; x++) {
        for(uint64_t y = 0; y < 280 - h[x]; y++)
            _hystogram.setPixel(x, y, qRgb(255, 0, 0));
        for(int y = 280 - h[x]; y < 280; y++)
            _hystogram.setPixel(x, y, qRgb(x, x, x));
    }
}

void ImageProcessor::apply_transformations(uint64_t position, bool force_apply) {
    if(source_status || _source_image.isNull())
        return;
    prev_transformation = prev_calculation(Transformations(position));
    _filtered_status = false;
    switch(position) {
        case Transformations::GRAY_SCALE: //gray scale
            _processed_image = _color_converter->gray_scale_image(_source_image);
            processing_list[Transformations::GRAY_SCALE] = _processed_image;
            prev_transformation = Transformations::GRAY_SCALE;

        case Transformations::BRIGHTNESS_CHANGE: //brightness change
            if(!_brightness_changer->_null_change || force_apply) {
                _processed_image = _brightness_changer->change_brightness(processing_list[prev_transformation]);
                processing_list[Transformations::BRIGHTNESS_CHANGE] = _processed_image;
                prev_transformation = Transformations::BRIGHTNESS_CHANGE;
                processing_status[Transformations::BRIGHTNESS_CHANGE] = true;
            }
            else
                processing_status[Transformations::BRIGHTNESS_CHANGE] = false;

        case Transformations::TRASHHOLD_NEGATIVE: //trashhold negative
            if(_negative_trashhold->_isOn || force_apply) {
                _processed_image = _negative_trashhold->negativize(processing_list[prev_transformation]);
                processing_list[Transformations::TRASHHOLD_NEGATIVE] = _processed_image;
                prev_transformation = Transformations::TRASHHOLD_NEGATIVE;
                processing_status[Transformations::TRASHHOLD_NEGATIVE] = true;
            }
            else
                processing_status[Transformations::TRASHHOLD_NEGATIVE] = false;

        case Transformations::CONTRAST: //contrast
            if(_contraster->_isOn || force_apply) {
                _processed_image = _contraster->change_contrast(processing_list[prev_transformation]);
                processing_list[Transformations::CONTRAST] = _processed_image;
                prev_transformation = Transformations::CONTRAST;
                processing_status[Transformations::CONTRAST] = true;
            }
            else
                processing_status[Transformations::CONTRAST] = false;

        case Transformations::GAMMA: //gamma
            if(_gammanizer->_isOn || force_apply) {
                _processed_image = _gammanizer->gammanize(processing_list[prev_transformation]);
                processing_list[Transformations::GAMMA] = _processed_image;
                prev_transformation = Transformations::GAMMA;
                processing_status[Transformations::GAMMA] = true;
            }
            else
                processing_status[Transformations::GAMMA] = false;

        case Transformations::BINARIZATION:; //binarization
            if(_binorizer->_isOn || force_apply) {
                _processed_image = _binorizer->binaryze(processing_list[prev_transformation]);
                processing_list[Transformations::BINARIZATION] = _processed_image;
                prev_transformation = Transformations::BINARIZATION;
                processing_status[Transformations::BINARIZATION] = true;
            }
            else
                processing_status[Transformations::BINARIZATION] = false;

        case Transformations::QUANTATION: //quantation
            if(_quantizer->_isOn || force_apply) {
                _processed_image = _quantizer->quantize(processing_list[prev_transformation]);
                processing_list[Transformations::QUANTATION] = _processed_image;
                prev_transformation = Transformations::QUANTATION;
                processing_status[Transformations::QUANTATION] = true;
            }
            else
                processing_status[Transformations::QUANTATION] = false;

        case Transformations::SOLARIZATION: //solarization
            if(_solarizer->_isOn || force_apply) {
                _processed_image = _solarizer->solarize(processing_list[prev_transformation]);
                processing_list[Transformations::SOLARIZATION] = _processed_image;
                prev_transformation = Transformations::SOLARIZATION;
                processing_status[Transformations::SOLARIZATION] = true;
            }
            else
                processing_status[Transformations::SOLARIZATION] = false;

        case Transformations::PSEUDO_COLORIZATION:; //pseudo colorize
            if(_pseudo_colorizer->_isOn || force_apply) {
                _processed_image = _pseudo_colorizer->pseudo_colorize(processing_list[prev_transformation]);
                processing_list[Transformations::PSEUDO_COLORIZATION] = _processed_image;
                prev_transformation = Transformations::PSEUDO_COLORIZATION;
                processing_status[Transformations::PSEUDO_COLORIZATION] = true;
            }
            else
                processing_status[Transformations::PSEUDO_COLORIZATION] = false;
    }
    calculate_hystogram();
}

uint64_t ImageProcessor::prev_calculation(Transformations transformation) {
    if(transformation > prev_transformation)
        return prev_transformation;
    for(int i = transformation - 1; i >= 0; i--)
        if(processing_status[i])
            if(i == Transformations::BINARIZATION && !_binorizer->_isOn)
                return prev_calculation(Transformations(i));
            else
                return uint64_t(i);
    return uint64_t(Transformations::GRAY_SCALE);
}

//Discussion moment with productivity of inline function. For now I will leave the code execution without a function. It seems to work faster
inline void ImageProcessor::transformation_fixation(Transformations transformation) {
    processing_list[transformation] = _processed_image;
    prev_transformation = transformation;
    processing_status[transformation] = true;
}
