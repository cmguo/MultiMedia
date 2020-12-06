#ifndef MEDIAPLAYERBRIDGE_H
#define MEDIAPLAYERBRIDGE_H

#include <QObject>


class MediaPlayerBridge : public QObject
{
    Q_OBJECT
public:
    explicit MediaPlayerBridge(QObject *parent =nullptr);

    virtual QObject * createPlayer() = 0;

    virtual QWidget * createSurface() = 0;
};

#endif // MEDIAPLAYERBRIDGE_H
