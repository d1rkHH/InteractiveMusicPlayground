INCLUDEPATH += ../../InteractiveMusicPlayground/InteractiveMusicPlayground/audioengine ../../InteractiveMusicPlayground/InteractiveMusicPlayground/audioengine/libaudiodecoder/include

HEADERS += ../../InteractiveMusicPlayground/InteractiveMusicPlayground/audioengine/audioengine.h \
           ../../InteractiveMusicPlayground/InteractiveMusicPlayground/audioengine/audioprocessor.h \
           ../../InteractiveMusicPlayground/InteractiveMusicPlayground/audioengine/audiosource.h \
           ../../InteractiveMusicPlayground/InteractiveMusicPlayground/audioengine/audiofile.h \
           ../../InteractiveMusicPlayground/InteractiveMusicPlayground/audioengine/audioplayer.h \
           ../../InteractiveMusicPlayground/InteractiveMusicPlayground/audioengine/libaudiodecoder/include/audiodecoder.h \
           ../../InteractiveMusicPlayground/InteractiveMusicPlayground/audioengine/libaudiodecoder/include/audiodecoderbase.h \
           ../../InteractiveMusicPlayground/InteractiveMusicPlayground/audioengine/channelbuffer.h


SOURCES +=  ../../InteractiveMusicPlayground/InteractiveMusicPlayground/audioengine/audiofile.cpp \
            ../../InteractiveMusicPlayground/InteractiveMusicPlayground/audioengine/audioplayer.cpp \
            ../../InteractiveMusicPlayground/InteractiveMusicPlayground/audioengine/audioengine.cpp \
            ../../InteractiveMusicPlayground/InteractiveMusicPlayground/audioengine/channelbuffer.cpp


win32{
    DEFINES += _WIN32
    HEADERS += ../../InteractiveMusicPlayground/InteractiveMusicPlayground/audioengine/libaudiodecoder/include/audiodecodermediafoundation.h
    SOURCES += ../../InteractiveMusicPlayground/InteractiveMusicPlayground/audioengine/libaudiodecoder/src/audiodecoderbase.cpp \
               ../../InteractiveMusicPlayground/InteractiveMusicPlayground/audioengine/libaudiodecoder/src/audiodecodermediafoundation.cpp
    LIBS    +=  -ldxva2 -lmf -levr -lmfplat -lmfplay -lmfreadwrite -lmfuuid -lole32
}
macx{
    HEADERS += ../../InteractiveMusicPlayground/InteractiveMusicPlayground/audioengine/libaudiodecoder/include/audiodecodercoreaudio.h
    SOURCES += ../../InteractiveMusicPlayground/InteractiveMusicPlayground/audioengine/libaudiodecoder/src/audiodecoderbase.cpp \
               ../../InteractiveMusicPlayground/InteractiveMusicPlayground/audioengine/libaudiodecoder/src/audiodecodercoreaudio.cpp
    LIBS += -framework CoreFoundation -framework AudioToolbox
}

