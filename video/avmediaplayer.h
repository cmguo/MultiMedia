#ifndef AVMEDIAPLAYER_H
#define AVMEDIAPLAYER_H

#include "mediaplayer.h"

#include <QtAV/AVPlayer.h>
#include <QtAVWidgets/VideoPreviewWidget.h>

#include <QUrl>
#include <QSize>

using namespace QtAV;

class AVMediaPlayer : public AVPlayer
{
    Q_OBJECT

    Q_PROPERTY(qint64 position READ position WRITE setPosition NOTIFY positionChanged)
    Q_PROPERTY(qreal volume READ volume WRITE setVolume NOTIFY volumeChanged)
    Q_PROPERTY(bool muted READ isMuted WRITE setMuted NOTIFY mutedChanged)
    Q_PROPERTY(QUrl source READ source WRITE setSource NOTIFY sourceChanged)
    Q_PROPERTY(MediaPlayer::State playState READ playState WRITE setPlayState NOTIFY playStateChanged)
    Q_PROPERTY(QWidget* surface READ surface WRITE setSurface NOTIFY surfaceChanged)
    Q_PROPERTY(QSize videoSize READ videoSize NOTIFY videoSizeChanged)
    Q_PROPERTY(QString error READ errorString)

public:
    Q_INVOKABLE AVMediaPlayer(QObject * parent =nullptr);

    virtual ~AVMediaPlayer() override;

public:
    qreal volume() const;

    void setVolume(qreal value);

    bool isMuted() const;

    void setMuted(bool m);

    QUrl source() const;

    void setSource(const QUrl & source);

    QWidget* surface();

    void setSurface(QWidget *);

    MediaPlayer::State playState()const;

    void setPlayState(MediaPlayer::State state);

    QSize videoSize() const;

    void setPosition(qint64 pos);

    qint64 position() const;

    QString errorString() const;

Q_SIGNALS:
    void volumeChanged();
    void mutedChanged();
    void surfaceChanged();
    void playStateChanged();
    void videoSizeChanged();
    void positionChanged(qint64 position);

private Q_SLOTS:
    void applyVolume();

private:
    QtAV::AVError error_;
    qreal volume_;
    bool mute_;
    bool preparedState_;
    bool loaded_;
    VideoPreviewWidget *preview_;
};

#endif // AVMEDIAPLAYER_H
