#include "avmediaplayer.h"
#include "avmediaplayerbridge.h"
#include "mediaplayer.h"

#include <QtAVWidgets/WidgetRenderer.h>

AVMediaPlayerBridge::AVMediaPlayerBridge(QObject *parent)
    : MediaPlayerBridge(parent)
{
}

QObject *AVMediaPlayerBridge::createPlayer()
{
    return new AVMediaPlayer(parent());
}

QWidget *AVMediaPlayerBridge::createSurface()
{
    return new WidgetRenderer();
}
