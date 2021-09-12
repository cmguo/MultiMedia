HEADERS += \
    $$PWD/controls.h \
    $$PWD/imagecontrol.h \
    $$PWD/strokecontrol.h \
    $$PWD/textcontrol.h \
    $$PWD/textinputcontrol.h \
    $$PWD/videocontrol.h \
    $$PWD/webcontrol.h

SOURCES += \
    $$PWD/imagecontrol.cpp \
    $$PWD/strokecontrol.cpp \
    $$PWD/textcontrol.cpp \
    $$PWD/textinputcontrol.cpp \
    $$PWD/videocontrol.cpp \
    $$PWD/webcontrol.cpp

win32 {
    HEADERS += \
        $$PWD/docxcontrol.h \
        $$PWD/pptxcontrol.h

    SOURCES += \
        $$PWD/docxcontrol.cpp \
        $$PWD/pptxcontrol.cpp
}
