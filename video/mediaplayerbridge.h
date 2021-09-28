#ifndef MEDIAPLAYERBRIDGE_H
#define MEDIAPLAYERBRIDGE_H

#include <QObject>
#include <QtQml>

class MediaPlayerBridge : public QObject
{
    Q_OBJECT
public:
    explicit MediaPlayerBridge(QObject *parent =nullptr);

    virtual QObject * createPlayer() = 0;

    virtual QWidget * createSurface() = 0;

public:
    static MediaPlayerBridge * get(QByteArray const & type);
};

#endif // MEDIAPLAYERBRIDGE_H
