#include "videocontroller.h"

#include <core/control.h>
#include <core/resourceview.h>

#include <QQmlContext>
#include <QGraphicsProxyWidget>

VideoController::VideoController(QWidget * parent)
    : QQuickWidget(parent)
{
    setResizeMode(QQuickWidget::SizeRootObjectToView);
    setAttribute(Qt::WA_TranslucentBackground);
    setClearColor(QColor(Qt::transparent));
    rootContext()->setContextProperty("quickWidgetParent", this);
    setVisible(false);
    if (parent) {
        QEvent e(QEvent::ParentChange);
        event(&e);
    }
}

void VideoController::sizeChanged()
{
    setVisible(true);
    setFixedSize(parentWidget()->size());
}

Control *VideoController::control()
{
    return Control::fromItem(parentWidget()->graphicsProxyWidget());
}

bool VideoController::event(QEvent *event)
{
    if (event->type() == QEvent::ParentChange) {
        if (parentWidget()) {
            setFixedSize(parentWidget()->size());
            rootContext()->setContextProperty(
                        "player", control()->property("player"));
            rootContext()->setContextProperty(
                        "control", QVariant::fromValue(control()));
            setSource(QUrl("qrc:/multimedia/qml/VideoPlayerBar.qml"));
            parentWidget()->installEventFilter(this);
            if (control()->property("fullScreen").toBool())
                setVisible(true);
        }
        return true;
    }
    return QQuickWidget::event(event);
}

bool VideoController::eventFilter(QObject *, QEvent *event)
{
    if (event->type() == QEvent::Resize)
        sizeChanged();
    return false;
}
