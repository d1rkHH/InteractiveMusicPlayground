QT       += core gui widgets multimedia

DEFINES += QT_NO_DEBUG_OUTPUT

TARGET = interactivemusicplayground
TEMPLATE = app

RESOURCES += audioresources.qrc

SOURCES += ../InteractiveMusicPlayground/main.cpp

include(interactivemusicplayground.pri)

