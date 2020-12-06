#ifndef QTMEDIAPLAYER_H
#define QTMEDIAPLAYER_H

#include "mediaplayer.h"

#include <QMediaPlayer>
#include <QSize>

class QtMediaPlayer : public QMediaPlayer
{
    Q_OBJECT

    Q_PROPERTY(QUrl source READ source WRITE setSource NOTIFY sourceChanged)
    Q_PROPERTY(MediaPlayer::State playState READ playState WRITE setPlayState NOTIFY playStateChanged)
    Q_PROPERTY(QWidget* surface READ surface WRITE setSurface NOTIFY surfaceChanged)
    Q_PROPERTY(QSize videoSize READ videoSize NOTIFY videoSizeChanged)
    Q_PROPERTY(qreal bufferProgress READ bufferProgress NOTIFY bufferProgressChanged)

public:
    explicit QtMediaPlayer(QObject *parent = nullptr);

signals:
    void sourceChanged();
    void surfaceChanged();
    void playStateChanged();
    void videoSizeChanged();
    void bufferProgressChanged();

public:
    QUrl source() const;

    void setSource(const QUrl & source);

    QWidget* surface();

    void setSurface(QWidget *);

    MediaPlayer::State playState()const;

    void setPlayState(MediaPlayer::State state);

    QSize videoSize() const;

    qreal bufferProgress() const;

private:
    QVideoWidget * surface_;
    MediaPlayer::State state_;
};

#endif // QTMEDIAPLAYER_H
