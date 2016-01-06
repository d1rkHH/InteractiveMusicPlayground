QT += core gui widgets multimedia

TARGET = IMPTest
CONFIG += console qtestlib
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += \
    impunittests.cpp

include(../InteractiveMusicPlayground/interactivemusicplayground.pri)
