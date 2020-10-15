QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    binarizer.cpp \
    brightnesschanger.cpp \
    colorconverter.cpp \
    contraster.cpp \
    gammanizer.cpp \
    highpassfilter.cpp \
    imageprocessor.cpp \
    lowpassfilter.cpp \
    main.cpp \
    mainwindow.cpp \
    negativetrashhold.cpp \
    pseudocolorizer.cpp \
    quantizer.cpp \
    solarizer.cpp \
    utility.cpp

HEADERS += \
    binarizer.h \
    brightnesschanger.h \
    colorconverter.h \
    contraster.h \
    gammanizer.h \
    highpassfilter.h \
    imageprocessor.h \
    lowpassfilter.h \
    mainwindow.h \
    negativetrashhold.h \
    pseudocolorizer.h \
    quantizer.h \
    solarizer.h \
    utility.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
