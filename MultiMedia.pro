QT += gui widgets webenginewidgets multimediawidgets quickwidgets

win32 { QT += axcontainer }

TEMPLATE = lib
CONFIG += plugin

CONFIG += c++11

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
    multimediaplugin.h

DISTFILES += MultiMedia.json

include(resources/resources.pri)
include(controls/controls.pri)
include(opengl/opengl.pri)
include(web/web.pri)
include(media/media.pri)

win32 {
    include(office/office.pri)
}

# Default rules for deployment.
unix {
    target.path = $$[QT_INSTALL_PLUGINS]/generic
}
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../QtComposition/release/ -lQtComposition
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../QtComposition/debug/ -lQtCompositiond
else:unix: LIBS += -L$$OUT_PWD/../QtComposition/ -lQtComposition

INCLUDEPATH += $$PWD/../QtComposition
DEPENDPATH += $$PWD/../QtComposition

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../QtEventBus/release/ -lQtEventBus
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../QtEventBus/debug/ -lQtEventBusd
else:unix: LIBS += -L$$OUT_PWD/../QtEventBus/ -lQtEventBus

INCLUDEPATH += $$PWD/../QtEventBus
DEPENDPATH += $$PWD/../QtEventBus

INCLUDEPATH += $$PWD/../QtPromise/src

INCLUDEPATH += $$PWD/../qtpromise/src/qtpromise $$PWD/../qtpromise/include
#DEPENDPATH += $$PWD/../qtpromise/src/qtpromise

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../ShowBoard/release/ -lShowBoard
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../ShowBoard/debug/ -lShowBoardd
else:unix: LIBS += -L$$OUT_PWD/../ShowBoard/ -lShowBoard

INCLUDEPATH += $$PWD/../ShowBoard
DEPENDPATH += $$PWD/../ShowBoard

win32:CONFIG(release, debug|release): LIBS += -lQtAV1 -lQtAVWidgets1
else:win32:CONFIG(debug, debug|release): LIBS += -lQtAVd1 -lQtAVWidgetsd1

INCLUDEPATH += $$OUT_PWD/../QtAV/include/

win32:CONFIG(debug, debug|release): {
    LIBS += -lGdiplus
}

