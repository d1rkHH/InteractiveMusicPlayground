#-------------------------------------------------
#
# Project created by QtCreator 2014-07-15T19:38:24
#
#-------------------------------------------------

INCLUDEPATH += ../InteractiveMusicPlayground/videoengine

SOURCES +=  ../../InteractiveMusicPlayground/InteractiveMusicPlayground/videoengine/videoengine.cpp \
            ../InteractiveMusicPlayground/videoengine/videowidget.cpp \
            ../InteractiveMusicPlayground/videoengine/videoformat.cpp
HEADERS  += ../InteractiveMusicPlayground/videoengine/videoengine.h \
            ../InteractiveMusicPlayground/videoengine/videowidget.h \
            ../InteractiveMusicPlayground/videoengine/cvmattoqimage.h \
            ../InteractiveMusicPlayground/videoengine/videoprocessor.h \
            ../InteractiveMusicPlayground/videoengine/videoformat.h

include(../videoengine/opencv.pri)
