QT += gui widgets webenginewidgets multimediawidgets quickwidgets

win32 { QT += axcontainer }

TEMPLATE = lib
DEFINES += MULTIMEDIA_LIBRARY
CONFIG += plugin

CONFIG += c++14

include($$(applyCommonConfig))
include($$(applyConanPlugin))

include(../config.pri)

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    multimediaplugin.cpp

HEADERS += \
    multimediaplugin.h \
    MultiMedia_global.h

RESOURCES += \
    $$PWD/res/MultiMedia.qrc

DISTFILES += MultiMedia.json

include(resources/resources.pri)
include(controls/controls.pri)
include(opengl/opengl.pri)
include(web/web.pri)
include(video/video.pri)
include(audio/audio.pri)
include(graphviz/graphviz.pri)

win32 {
    include(office/office.pri)
}

# Default rules for deployment.
unix {
    target.path = $$[QT_INSTALL_PLUGINS]/generic
}
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(debug, debug|release): {
    LIBS += -lGdiplus
}

exists("D:/Program Files/Graphviz/include") {

    DEFINES += HAS_GRAPHVIZ
    win32: LIBS += -L"D:/Program Files/Graphviz/lib" -lgvc -lcdt -lcgraph \
        -lgvplugin_core -lgvplugin_dot_layout -lgvplugin_gdiplus -lgvplugin_neato_layout -lgvplugin_pango
    INCLUDEPATH += "D:/Program Files/Graphviz/include"
}

