#include "volumebar.h"

#include <QTimer>
#include <QQmlContext>

VolumeBar::VolumeBar(QWidget *parent)
    : QQuickWidget(parent)
{
    setResizeMode(QQuickWidget::SizeViewToRootObject);
    setWindowFlag(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    setClearColor(QColor(Qt::transparent));
    rootContext()->setContextProperty("quickWidgetParent", this);
    setSource(QUrl("qrc:/multimedia/qml/VolumeBar.qml"));
}

double VolumeBar::volume() const
{
    return mVolume;
}

void VolumeBar::setVolume(double v)
{
    if (mVolume == v) return;

    mVolume = v;
    emit volumeChanged();
}

bool VolumeBar::upDown() const
{
    return mUpDown;
}

void VolumeBar::setUpDown(bool upDown)
{
    mUpDown = upDown;
    emit changed();
}

bool VolumeBar::event(QEvent * event)
{
    switch (event->type()) {
    case QEvent::Show:
        timerCancelFlag_ = true;
        this->setFocus();
        break;
    case QEvent::FocusOut:
        timerCancelFlag_ = false;
        QTimer::singleShot(300,this, [this]() {
            if(!timerCancelFlag_) {
                this->hide();
            }
        });
        break;
    default:
        return QQuickWidget::event(event);
    }
    return true;
}
