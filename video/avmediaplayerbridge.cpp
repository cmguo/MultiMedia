#include "avmediaplayer.h"
#include "avmediaplayerbridge.h"
#include "mediaplayer.h"

#include <QtAVWidgets/WidgetRenderer.h>
#include <QtQml>

AVMediaPlayerBridge::AVMediaPlayerBridge(QObject *parent)
    : MediaPlayerBridge(parent)
{
    qmlRegisterType<MediaPlayer>("MediaPlayer", 1, 0, "MediaPlayer");
}

QObject *AVMediaPlayerBridge::createPlayer()
{
    return new AVMediaPlayer(parent());
}

QWidget *AVMediaPlayerBridge::createSurface()
{
    return new WidgetRenderer();
}
