HEADERS += \
    $$PWD/controls.h \
    $$PWD/docxcontrol.h \
    $$PWD/imagecontrol.h \
    $$PWD/strokecontrol.h \
    $$PWD/textcontrol.h \
    $$PWD/videocontrol.h \
    $$PWD/webcontrol.h \
    $$PWD/wordscontrol.h

SOURCES += \
    $$PWD/docxcontrol.cpp \
    $$PWD/imagecontrol.cpp \
    $$PWD/strokecontrol.cpp \
    $$PWD/textcontrol.cpp \
    $$PWD/videocontrol.cpp \
    $$PWD/webcontrol.cpp \
    $$PWD/wordscontrol.cpp

win32 {
    HEADERS += \
        $$PWD/pptxcontrol.h

    SOURCES += \
        $$PWD/pptxcontrol.cpp
}
