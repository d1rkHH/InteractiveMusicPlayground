#-------------------------------------------------
#
# Project created by QtCreator 2014-07-15T19:38:24
#
#-------------------------------------------------

QT       += core gui widgets



TARGET = ColorKeyer
TEMPLATE = app


SOURCES += main.cpp\
        videoplayer.cpp \
    colorkeyer.cpp

HEADERS  += videoplayer.h \
    colorkeyer.h

FORMS    += videoplayer.ui

include(../videoengine/videoengine.pri)
include(../audioengine/audioengine.pri)
include(../Oscillator/oscillator.pri)
