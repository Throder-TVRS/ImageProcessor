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
                   HighPassFilter *highpass_filter);

    QString _filepath;
    QImage _default_size_source_image;
    QImage _source_image;
    QImage _processed_image;
    QImage _filtered_image;
    bool source_status = false;
    bool _filtered_status = false;
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
    std::vector <QImage> processing_list;
    std::vector <bool> processing_status;

    void load_image(const QString& filepath);
    void save_image(QString format);
    void calculate_hystogram();
    void apply_transformations(uint64_t position, bool force_apply);
    uint64_t prev_calculation(Transformations transformation);
    void transformation_fixation(Transformations transformation);
};

#endif // IMAGEPROCESSOR_H
