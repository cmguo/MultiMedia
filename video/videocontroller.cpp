#include "videocontroller.h"

#include <core/control.h>
#include <core/resourceview.h>

#include <feedback/feedbackpopupwindow.h>

#include <QQmlContext>
#include <QGraphicsProxyWidget>

VideoController::VideoController(QWidget * parent)
    : TalQuickWidget(parent)
{
    setVisible(false);
    if (parent) {
        QEvent e(QEvent::ParentChange);
        event(&e);
    }
}

bool VideoController::enableFeedBack() const
{
    Control * ctrl = Control::fromItem(parentWidget()->graphicsProxyWidget());
    return ctrl->resource()->property("enableFeedBack").toBool();
}

void VideoController::feedback(QPointF locationFromRoot)
{
    if (control()->property("fullScreen").toBool()) {
        QObject * another = control()->property("player").value<QObject*>()->parent();
        VideoController * another2 = another->property("controller").value<VideoController*>();
        another2->feedback({0, 0});
        control()->setProperty("fullScreen", false);
        return;
    }

    int resourceType = property("teachingResourceType").toInt();
    QString resourceId = property("teachingResourceId").toString();

    QPoint rootLocation = parentWidget()->mapToGlobal({0, 0});
    rootLocation += locationFromRoot.toPoint();
    FeedbackPopupWindow::showFeedback(rootLocation, resourceType, resourceId);
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
            setSource(QUrl("qrc:/resource/qml/VideoPlayerBar.qml"));
            rootContext()->setContextProperty(
                        "player", control()->property("player"));
            rootContext()->setContextProperty(
                        "control", QVariant::fromValue(control()));
            parentWidget()->installEventFilter(this);
            if (control()->property("fullScreen").toBool())
                setVisible(true);
        }
        return true;
    }
    return TalQuickWidget::event(event);
}

bool VideoController::eventFilter(QObject *, QEvent *event)
{
    if (event->type() == QEvent::Resize)
        sizeChanged();
    return false;
}
