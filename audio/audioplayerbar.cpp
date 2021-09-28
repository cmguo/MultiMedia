#include "audioplayerbar.h"

#include <QQmlContext>
#include <QQuickItem>

#include <views/qsshelper.h>

AudioPlayerBar::AudioPlayerBar(QWidget *parent)
    : QQuickWidget(parent),
      mMediaUrl(QUrl()), mMediaTitle(""),
      mVolumeBar(new VolumeBar(parent))
{
    mVolumeBar->hide();

    setResizeMode(QQuickWidget::SizeViewToRootObject);
    //setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    setStyleSheet("background-color:transparent;");
    setClearColor(QColor(Qt::transparent));

    rootContext()->setContextProperty("quickWidgetParent", this);
    rootContext()->setContextProperty("volumeBar", mVolumeBar);
    setSource(QUrl("qrc:/multimedia/qml/AudioPlayerBar.qml"));

    initItemGeometry();
}

QUrl AudioPlayerBar::mediaUrl() const
{
    return mMediaUrl;
}

void AudioPlayerBar::setMediaUrl(QUrl url)
{
    if (url == mMediaUrl) return;
    mMediaUrl = url;
    emit mediaUrlChanged();
}

QString AudioPlayerBar::mediaTitle() const
{
    return mMediaTitle;
}

void AudioPlayerBar::setMediaTitle(QString title)
{
    if (title == mMediaTitle) return;
    mMediaTitle = title;
    emit mediaTitleChanged();
}

bool AudioPlayerBar::canResize() const
{
    return mCanResize;
}

void AudioPlayerBar::setCanResize(bool b)
{
    if (mCanResize == b) return;
    mCanResize = b;
    emit canResizeChanged();
}

bool AudioPlayerBar::closable() const
{
    return mClosable;
}

void AudioPlayerBar::setClosable(bool b)
{
    mClosable = b;
}

void AudioPlayerBar::volumeClick()
{
    if (mVolumeBar->isVisible()) {
        mVolumeBar->hide();
    } else {
        QPoint position = mapToGlobal({0, 0});
        int x = position.x() + width() - dp(86) - mVolumeBar->width();
        int y = 0;
        if(position.y() < (mVolumeBar->height() + dp(10))) {
            y = position.y() + this ->height() + dp(5);
            mVolumeBar->setProperty("upDown",true);
        } else {
            y = position.y() - mVolumeBar->height() - dp(5);
            mVolumeBar->setProperty("upDown",false);
        }
        mVolumeBar->move(x,y);
        mVolumeBar->show();
    }
}

void AudioPlayerBar::closeClick()
{
    if (mClosable) {
        close();
    } else {
        emit closeSignal();
    }
}

void AudioPlayerBar::checkAndHideVolume()
{
    if (mVolumeBar != nullptr && mVolumeBar->isVisible()) {
        mVolumeBar->hide();
    }
}

void AudioPlayerBar::resizeEvent(QResizeEvent *event)
{
    QQuickWidget::resizeEvent(event);

    if (!mCanResize) return;
    QPoint position = pos();

    if (event->oldSize().height() != event->size().height()) {
        move(position.x(), position.y() - (event->size().height() - event->oldSize().height()));
    }
    if (event->oldSize().width() < event->size().width()) {
        // 解决折叠后播放器靠屏幕右边，展开时超出屏幕的问题
//        if (position.x() + event->size().width() > QssHelper::getScreenWidth()) {
//            move(QssHelper::getScreenWidth() - event->size().width(), position.y());
//        }
    }
}

QRect AudioPlayerBar::itemGeometry(QString objectName)
{
    QQuickItem *item = rootObject()->findChild<QQuickItem *>(objectName);
    QPointF position = item->mapToGlobal({0, 0}) - pos();

    return QRect(position.x(), position.y(), item->width(), item->height());
}

void AudioPlayerBar::initItemGeometry()
{
    mPlayerBarRect = itemGeometry("audioPlayerBar");
    mSeekBarRect = itemGeometry("seekSlider");
    mVolumeButtonRect = itemGeometry("volumeButton");
}
