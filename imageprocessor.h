#ifndef IMAGEPROCESSOR_H
#define IMAGEPROCESSOR_H
#include <QColorDialog>

#include "colorconverter.h"
#include "brightnesschanger.h"
#include "negativetrashhold.h"
#include "binarizer.h"
#include "contraster.h"
#include "gammanizer.h"
#include "pseudocolorizer.h"
#include "solarizer.h"
#include "quantizer.h"
#include "lowpassfilter.h"
#include "highpassfilter.h"
#include "medianfilter.h"
#include "gaussianfilter.h"

class ColorConverter;
class BrightnessChanger;
class NegativeTrashhold;
class Binarizer;
class Contraster;
class Gammanizer;
class PseudoColorizer;
class Solarizer;
class Quantizer;
class LowPassFilter;
class HighPassFilter;
class MedianFilter;
class GaussianFilter;

enum Transformations {
    GRAY_SCALE,
    BRIGHTNESS_CHANGE,
    TRASHHOLD_NEGATIVE,
    CONTRAST,
    GAMMA,
    BINARIZATION,
    QUANTATION,
    SOLARIZATION,
    PSEUDO_COLORIZATION
};

enum Token {
    LOWPASS,
    HIGHPASS,
    MEDIAN,
    GAUSSIAN
};

struct FilterToken {
    Token transform;
    uint64_t param;
};

class ImageProcessor {
public:
    ImageProcessor(ColorConverter *color_converter,
                   BrightnessChanger *brightness_changer,
                   NegativeTrashhold *negative_trashhold,
                   Binarizer *binarizator,
                   Contraster * contraster,
                   Gammanizer *gammanizator,
                   PseudoColorizer *pseudo_colorizer,
                   Solarizer *solarizator,
                   Quantizer *quantizer,
                   LowPassFilter *lowpass_filter,
                   HighPassFilter *highpass_filter,
                   MedianFilter *median_filter,
                   GaussianFilter *gaussian_filter);

    QString _filepath;
    QImage _default_size_source_image;
    QImage _source_image;
    QImage _processed_image;
    QImage _filtered_image;
    bool source_status = false;
    bool _filtered_status = false;
    bool _reset_mode = false;
    QImage _hystogram;
    const uint64_t _preview_label_size = 711;
    uint64_t prev_transformation;
    uint64_t _transformations_amount;

    ColorConverter *_color_converter;
    BrightnessChanger *_brightness_changer;
    NegativeTrashhold *_negative_trashhold;
    Binarizer *_binorizer;
    Contraster * _contraster;
    Gammanizer *_gammanizer;
    Quantizer *_quantizer;
    PseudoColorizer *_pseudo_colorizer;
    Solarizer *_solarizer;
    LowPassFilter *_lowpass_filter;
    HighPassFilter *_highpass_filter;
    MedianFilter *_median_filter;
    GaussianFilter *_gaussian_filter;
    std::vector <QImage> processing_list;
    std::vector <bool> processing_status;
    std::vector<FilterToken> filtering_queue;

    void load_image(const QString& filepath);
    void save_image();
    void calculate_hystogram();
    void apply_transformations(uint64_t position, bool force_apply);
    uint64_t prev_calculation(Transformations transformation);
    void transformation_fixation(Transformations transformation);
};

#endif // IMAGEPROCESSOR_H
