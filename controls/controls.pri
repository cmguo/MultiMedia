HEADERS += \
    $$PWD/animatedcontrol.h \
    $$PWD/audiocontrol.h \
    $$PWD/controls.h \
    $$PWD/graphvizcontrol.h \
    $$PWD/imagecontrol.h \
    $$PWD/strokecontrol.h \
    $$PWD/textcontrol.h \
    $$PWD/textinputcontrol.h \
    $$PWD/vectorcontrol.h \
    $$PWD/videocontrol.h

SOURCES += \
    $$PWD/animatedcontrol.cpp \
    $$PWD/audiocontrol.cpp \
    $$PWD/graphvizcontrol.cpp \
    $$PWD/imagecontrol.cpp \
    $$PWD/strokecontrol.cpp \
    $$PWD/textcontrol.cpp \
    $$PWD/textinputcontrol.cpp \
    $$PWD/vectorcontrol.cpp \
    $$PWD/videocontrol.cpp

win32 {
    HEADERS += \
        $$PWD/docxcontrol.h \
        $$PWD/pptxcontrol.h

    SOURCES += \
        $$PWD/docxcontrol.cpp \
        $$PWD/pptxcontrol.cpp
}

!showboard_quick: {

    HEADERS += \
        $$PWD/webcontrol.h

    SOURCES += \
        $$PWD/webcontrol.cpp

}

