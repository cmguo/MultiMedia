#include "qtmediaplayer.h"
#include "qtmediaplayerbridge.h"

#include <QVideoWidget>

QtMediaPlayerBridge::QtMediaPlayerBridge(QObject *parent)
    : MediaPlayerBridge(parent)
{
}

QObject *QtMediaPlayerBridge::createPlayer()
{
    return new QtMediaPlayer;
}

QWidget *QtMediaPlayerBridge::createSurface()
{
    return new QVideoWidget;
}
