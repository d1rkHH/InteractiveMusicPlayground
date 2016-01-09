INCLUDEPATH += ../InteractiveMusicPlayground

HEADERS  += ../InteractiveMusicPlayground/videoplayer.h \
    ../InteractiveMusicPlayground/musicchip.h \
    ../InteractiveMusicPlayground/effectprocessor.h \
    ../InteractiveMusicPlayground/soundcontrol.h \
    ../InteractiveMusicPlayground/shapes.h \
    ../InteractiveMusicPlayground/musicchipplayer.h \
    ../InteractiveMusicPlayground/colorrange.h \
    ../InteractiveMusicPlayground/imageprocessor.h \
    ../InteractiveMusicPlayground/effect.h \
    ../InteractiveMusicPlayground/highpasseffect.h \
    $$PWD/delayeffect.h \
    $$PWD/ringbuffer.h \
    $$PWD/lowpasseffect.h

SOURCES +=  ../InteractiveMusicPlayground/videoplayer.cpp \
    ../InteractiveMusicPlayground/imageprocessor.cpp \
    ../InteractiveMusicPlayground/musicchip.cpp \
    ../InteractiveMusicPlayground/colorrange.cpp \
    ../InteractiveMusicPlayground/effectprocessor.cpp \
    ../InteractiveMusicPlayground/soundcontrol.cpp \
    ../InteractiveMusicPlayground/musicchipplayer.cpp \
    ../InteractiveMusicPlayground/imageprocessor.cpp \
    ../InteractiveMusicPlayground/highpasseffect.cpp \
    $$PWD/delayeffect.cpp \
    $$PWD/ringbuffer.cpp \
    $$PWD/lowpasseffect.cpp

FORMS    += ../InteractiveMusicPlayground/videoplayer.ui

include(audioengine/audioengine.pri)
include(videoengine/videoengine.pri)
