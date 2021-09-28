HEADERS += \
    $$PWD/exports.h \
    $$PWD/mediaplayer.h \
    $$PWD/mediaplayerbridge.h \
    $$PWD/qtmediaplayer.h \
    $$PWD/qtmediaplayerbridge.h \
    $$PWD/videocontroller.h

SOURCES += \
    $$PWD/mediaplayer.cpp \
    $$PWD/mediaplayerbridge.cpp \
    $$PWD/qtmediaplayer.cpp \
    $$PWD/qtmediaplayerbridge.cpp \
    $$PWD/videocontroller.cpp

win32 {

    HEADERS += \
        $$PWD/avmediaplayer.h \
        $$PWD/avmediaplayerbridge.h \

    SOURCES += \
        $$PWD/avmediaplayer.cpp \
        $$PWD/avmediaplayerbridge.cpp \

}
