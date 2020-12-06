#include "avmediaplayer.h"

#include <QtAVWidgets/WidgetRenderer.h>
#include <QTimer>
#include <QUrl>
#include <QDebug>

#define PRE_CAPTURE_ENABLE 0

using namespace QtAV;

AVMediaPlayer::AVMediaPlayer(QObject *parent)
    : AVPlayer(parent)
    , volume_(1.0)
    , mute_(false)
    , preparedState_(false)
    , loaded_(false)
    , preview_(nullptr)
{
    //setBufferMode(BufferMode::BufferPackets);
    setAsyncLoad(true);
    setAutoLoad(true);
    connect(this, &AVPlayer::stateChanged, this, &AVMediaPlayer::playStateChanged);
    connect(this, &AVPlayer::stopped, this, &AVMediaPlayer::playStateChanged);
    connect(this, &AVPlayer::started, this, &AVMediaPlayer::playStateChanged);
    connect(this, &AVPlayer::paused, this, &AVMediaPlayer::playStateChanged);
    connect(this, &AVPlayer::mediaStatusChanged, this, &AVMediaPlayer::playStateChanged);
    connect(this, &AVPlayer::mediaStatusChanged, this, &AVMediaPlayer::positionChanged);
    connect(this, &AVPlayer::positionChanged, this, &AVMediaPlayer::positionChanged);
    connect(audio(), &AudioOutput::volumeChanged, this, &AVMediaPlayer::applyVolume, Qt::DirectConnection);
    connect(audio(), &AudioOutput::muteChanged, this, &AVMediaPlayer::applyVolume, Qt::DirectConnection);
    connect(this, &AVPlayer::started, this, &AVMediaPlayer::applyVolume);
    connect(this, &AVPlayer::started, this, [this]() { preparedState_ = false;});
    connect(this, &AVPlayer::error, this, [this] (auto e) { error_ = e; });
    connect(this, &AVPlayer::loaded, this, [this]() {
        if (loaded_)
            return;
        loaded_ = true;
        preparedState_ = true;
        connect(this, &AVPlayer::mediaStatusChanged, this,[this](QtAV::MediaStatus status){
            if(status == QtAV::MediaStatus::BufferedMedia && !property("autoPause").toBool()){
                QTimer::singleShot(800, this,[this](){
                    pause(true);
                });
                setProperty("autoPause",true);
            }
        },Qt::DirectConnection);
        play();
        emit videoSizeChanged();
        emit playStateChanged();
    });
}

AVMediaPlayer::~AVMediaPlayer()
{
    stop();
}
#if PRE_CAPTURE_ENABLE
void AVMediaPlayer::onTimeSliderHover(int pos, int value)
{

    QToolTip::showText(QPoint(pos, 0), QTime(0, 0, 0).addMSecs(value).toString(QString::fromLatin1("HH:mm:ss")));
    int w = 240;
    int h=135;
    if (!preview_){
        preview_ = new VideoPreviewWidget();
        preview_->setAutoDisplayFrame(true);
        preview_->setFile(player_->file());
        preview_->setWindowFlags(Qt::Tool |Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint);
        preview_->resize(w, h);
        preview_->move(QPoint(pos, 0) + QPoint(w/2, 800));
    }
    preview_->setTimestamp(value);
    preview_->preview();
    preview_->show();

}


void AVMediaPlayer::onTimeSliderLeave()
{
    if (!preview_)
    {
        return;
    }
    if (preview_->isVisible())
    {
        preview_->hide();
    }
}
#endif


qreal AVMediaPlayer::volume() const
{
    return volume_;
}

void AVMediaPlayer::setVolume(qreal value)
{
    if (volume_ < 0) {
        qWarning("volume must > 0");
        return;
    }
    if (qFuzzyCompare(volume_ + 1.0, value + 1.0))
        return;
    volume_ = value;
    Q_EMIT volumeChanged();
    applyVolume();
}

bool AVMediaPlayer::isMuted() const
{
    return mute_;
}

void AVMediaPlayer::setMuted(bool m)
{
    if (isMuted() == m)
        return;
    mute_ = m;
    Q_EMIT mutedChanged();
    applyVolume();
}

QUrl AVMediaPlayer::source() const
{
    return file();
}

void AVMediaPlayer::setSource(const QUrl & url)
{
    setFile(url.toEncoded());
    load();
}

QWidget *AVMediaPlayer::surface()
{
    return static_cast<WidgetRenderer *>(renderer());
}

void AVMediaPlayer::setSurface(QWidget * render)
{
    WidgetRenderer * widgetRender =static_cast<WidgetRenderer *>(render) ;
    setRenderer(widgetRender);
}

MediaPlayer::State AVMediaPlayer::playState() const
{
    if (error_.error())
        return MediaPlayer::State::ErrorState;
    if (preparedState_)
        return MediaPlayer::State::PreparedState;
    if (state() == AVPlayer::State::PlayingState)
        return MediaPlayer::State::PlayingState;
    if (state() == AVPlayer::State::PausedState)
        return MediaPlayer::State::PausedState;
    if (state() == AVPlayer::State::StoppedState)
        return MediaPlayer::State::StoppedState;
    return MediaPlayer::IdleState;
}

void AVMediaPlayer::setPlayState(MediaPlayer::State state)
{
    switch (state) {
    case MediaPlayer::State::PausedState:
        pause(true);
        break;
    case MediaPlayer::State::StoppedState:
        stop();
        break;
    case MediaPlayer::State::PlayingState:
        isPlaying()?pause(false):play();
        break;
    default:
        break;
    }
}

QSize AVMediaPlayer::videoSize() const
{
    return QSize(statistics().video_only.width,statistics().video_only.height);
}

void AVMediaPlayer::setPosition(qint64 pos)
{
    if(isPlaying())
        AVPlayer::setPosition(pos);
    else
        AVPlayer::setStartPosition(pos);
    emit positionChanged(position());
}

qint64 AVMediaPlayer::position() const
{
    if (isPlaying())
        return AVPlayer::position();
    return AVPlayer::startPosition();
}

QString AVMediaPlayer::errorString() const
{
    return error_.string();
}

void AVMediaPlayer::applyVolume()
{
    AudioOutput *ao = audio();
    if (!ao || !ao->isAvailable())
        return;
    if (!sender() || qobject_cast<AudioOutput*>(sender()) != ao) {
        ao->setVolume(volume());
        ao->setMute(isMuted());
        return;
    }
    setVolume(ao->volume());
    setMuted(ao->isMute());
}
