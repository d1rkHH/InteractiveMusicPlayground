#-------------------------------------------------
#
# Project created by QtCreator 2014-07-15T19:38:24
#
#-------------------------------------------------

QT       += core gui widgets multimedia



TARGET = ColorKeyer
TEMPLATE = app


SOURCES += main.cpp\
        videoplayer.cpp \
    colorkeyer.cpp \
    musicchip.cpp

HEADERS  += videoplayer.h \
    colorkeyer.h \
    musicchip.h

FORMS    += videoplayer.ui

include(../videoengine/videoengine.pri)
include(../audioengine/audioengine.pri)
include(../Oscillator/oscillator.pri)
