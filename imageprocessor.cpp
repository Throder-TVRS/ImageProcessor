#include "imageprocessor.h"

ImageProcessor::ImageProcessor(ColorConverter *color_converter,
                               BrightnessChanger *brightness_changer,
                               NegativeTrashhold *negative_trashhold,
                               Binarizator *binarizator,
                               Contraster *contraster,
                               Gammanizator *gammanizator,
                               PseudoColorizer *pseudo_colorizer)
    : _color_converter(color_converter)
    , _brightness_changer(brightness_changer)
    , _negative_trashhold(negative_trashhold)
    , _binarizator(binarizator)
    , _contraster(contraster)
    , _gammanizator(gammanizator)
    , _pseudo_colorizer(pseudo_colorizer) {

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

void ImageProcessor::save_image(QString format) {

}

void ImageProcessor::calculate_hystogram() {
    uint64_t h_max = 0, k;
    std::vector<uint64_t> h(256, 0);
    for(int y = 0; y < _processed_image.height(); y++) {
        for(int x = 0; x < _processed_image.width(); x++) {
            k = _processed_image.pixelColor(x, y).red();
            h[k]++;
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
            if(_gammanizator->_isOn || force_apply) {
                _processed_image = _gammanizator->gammanize(processing_list[prev_transformation]);
                processing_list[Transformations::GAMMA] = _processed_image;
                prev_transformation = Transformations::GAMMA;
            }
        case Transformations::BINARIZATION:; //binarization
            if(_binarizator->_isOn || force_apply) {
                _processed_image = _binarizator->binaryze(processing_list[prev_transformation]);
                processing_list[Transformations::BINARIZATION] = _processed_image;
                prev_transformation = Transformations::BINARIZATION;
                processing_status[Transformations::BINARIZATION] = true;
            }
            else
                processing_status[Transformations::BINARIZATION] = false;
        case Transformations::PSEUDO_COLORIZER:; //pseudo colorize
            if(_pseudo_colorizer->_isOn || force_apply) {
                _processed_image = _pseudo_colorizer->pseudo_colorize(processing_list[prev_transformation]);
                processing_list[Transformations::PSEUDO_COLORIZER] = _processed_image;
                prev_transformation = Transformations::PSEUDO_COLORIZER;
                processing_status[Transformations::PSEUDO_COLORIZER] = true;
            }
            else
                processing_status[Transformations::PSEUDO_COLORIZER] = false;
    }
    calculate_hystogram();
}

uint64_t ImageProcessor::prev_calculation(Transformations transformation) {
    if(transformation > prev_transformation)
        return transformation;
    for(int i = transformation - 1; i >= 0; i--)
        if(processing_status[i])
            return uint64_t(i);
    return Transformations::GRAY_SCALE;
}
