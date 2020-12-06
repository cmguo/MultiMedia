#include "qtmediaplayer.h"

#include <QMediaService>
#include <QVideoRendererControl>
#include <QVideoWidget>

QtMediaPlayer::QtMediaPlayer(QObject *parent)
    : QMediaPlayer(parent)
    , surface_(nullptr)
    , state_(MediaPlayer::IdleState)
{
    connect(this, &QMediaPlayer::stateChanged, this, [this] (auto newState) {
        MediaPlayer::State state = MediaPlayer::IdleState;
        switch (newState) {
        case StoppedState:
            state = MediaPlayer::StoppedState;
            break;
        case PlayingState:
            state = MediaPlayer::PlayingState;
            break;
        case PausedState:
            state = MediaPlayer::PausedState;
            break;
        }
        state_ = state;
        emit playStateChanged();
    });
    connect(this, &QMediaPlayer::mediaStatusChanged, this, [this] (auto status) {
        switch (status) {
        case LoadedMedia:
            state_ = MediaPlayer::PreparedState;
            emit playStateChanged();
            break;
        case StalledMedia:
        case BufferingMedia:
        case BufferedMedia:
            break;
        }
    });
    void (QMediaPlayer::*error)(QMediaPlayer::Error error) = &QMediaPlayer::error;
    connect(this, error, this, [this] (auto) {
        state_ = MediaPlayer::ErrorState;
        emit playStateChanged();
    });
}

QUrl QtMediaPlayer::source() const
{
    return media().canonicalUrl();
}

void QtMediaPlayer::setSource(const QUrl &source)
{
    setMedia(source);
}

QWidget *QtMediaPlayer::surface()
{
    return nullptr;
}

void QtMediaPlayer::setSurface(QWidget * surface)
{
    auto vw = qobject_cast<QVideoWidget*>(surface);
    if (vw == surface_)
        return;
    setVideoOutput(vw);
    if (surface_)
        surface_->disconnect(this);
    surface = vw;
//    if (surface_)
    //        connect(surface_, QVideoWidget::);
}

MediaPlayer::State QtMediaPlayer::playState() const
{
    return state_;
}

void QtMediaPlayer::setPlayState(MediaPlayer::State state)
{
    if (state == state_)
        return;
    switch (state) {
    case MediaPlayer::StoppedState:
        stop();
        break;
    case MediaPlayer::PlayingState:
        play();
        break;
    case MediaPlayer::PausedState:
        if (state != MediaPlayer::PlayingState)
            return;
        play();
        break;
    default:
        return;
    }
    state_ = state;
}

QSize QtMediaPlayer::videoSize() const
{
    return {600, 400};
}

qreal QtMediaPlayer::bufferProgress() const
{
    return qreal(bufferStatus()) / 100;
}
