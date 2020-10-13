#ifndef IMAGEPROCESSOR_H
#define IMAGEPROCESSOR_H
#include "colorconverter.h"
#include "brightnesschanger.h"
#include "negativetrashhold.h"
#include "binarizator.h"
#include "contraster.h"
#include "gammanizator.h"
#include "pseudocolorizer.h"
class ColorConverter;
class BrightnessChanger;
class NegativeTrashhold;
class Binarizator;
class Contraster;
class Gammanizator;
class PseudoColorizer;

enum Transformations {
    GRAY_SCALE,
    BRIGHTNESS_CHANGE,
    TRASHHOLD_NEGATIVE,
    CONTRAST,
    GAMMA,
    BINARIZATION,
    PSEUDO_COLORIZER
};

class ImageProcessor {
public:
    ImageProcessor(ColorConverter *color_converter,
                   BrightnessChanger *brightness_changer,
                   NegativeTrashhold *negative_trashhold,
                   Binarizator *binarizator,
                   Contraster * contraster,
                   Gammanizator *gammanizator,
                   PseudoColorizer *pseudo_colorizer);

    QString _filepath;
    QImage _default_size_source_image;
    QImage _source_image;
    QImage _processed_image;
    bool source_status = false;
    QImage _hystogram;
    const uint64_t _preview_label_size = 711;
    uint64_t prev_transformation;
    uint64_t _transformations_amount;

    ColorConverter *_color_converter;
    BrightnessChanger *_brightness_changer;
    NegativeTrashhold *_negative_trashhold;
    Binarizator *_binarizator;
    Contraster * _contraster;
    Gammanizator *_gammanizator;
    PseudoColorizer *_pseudo_colorizer;
    std::vector <QImage> processing_list;
    std::vector <bool> processing_status;

    void load_image(const QString& filepath);
    void save_image(QString format);
    void calculate_hystogram();
    void apply_transformations(uint64_t position, bool force_apply);
    uint64_t prev_calculation(Transformations transformation);
};

#endif // IMAGEPROCESSOR_H
