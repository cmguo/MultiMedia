#ifndef AVMEDIAPLAYERBRIDGE_H
#define AVMEDIAPLAYERBRIDGE_H

#include "mediaplayerbridge.h"

class AVMediaPlayerBridge : public MediaPlayerBridge
{
    Q_OBJECT
public:
    Q_INVOKABLE AVMediaPlayerBridge(QObject *parent = nullptr);

    virtual QObject *createPlayer() override;

    virtual QWidget *createSurface() override;
};

#endif // AVMEDIAPLAYERBRIDGE_H
