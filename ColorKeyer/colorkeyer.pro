#-------------------------------------------------
#
# Project created by QtCreator 2014-07-15T19:38:24
#
#-------------------------------------------------

QT       += core gui widgets multimedia


DEFINES += QT_NO_DEBUG_OUTPUT



TARGET = ColorKeyer
TEMPLATE = app


SOURCES += main.cpp\
        videoplayer.cpp \
    colorkeyer.cpp \
    musicchip.cpp \
    colorrange.cpp \
    effectprocessor.cpp \
    soundcontrol.cpp \
    musicchipplayer.cpp

HEADERS  += videoplayer.h \
    colorkeyer.h \
    musicchip.h \
    colorrange.h \
    effectprocessor.h \
    soundcontrol.h \
    shapes.h \
    musicchipplayer.h

FORMS    += videoplayer.ui

include(../videoengine/videoengine.pri)
include(../audioengine/audioengine.pri)
include(../Oscillator/oscillator.pri)
