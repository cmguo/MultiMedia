#ifndef QTMEDIAPLAYERBRIDGE_H
#define QTMEDIAPLAYERBRIDGE_H

#include <video/mediaplayerbridge.h>

class QtMediaPlayerBridge : public MediaPlayerBridge
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit QtMediaPlayerBridge(QObject *parent = nullptr);

    virtual QObject *createPlayer() override;

    virtual QWidget *createSurface() override;
};

#endif // QTMEDIAPLAYERBRIDGE_H
