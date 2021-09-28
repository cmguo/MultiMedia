#include "videocontrol.h"
#include <video/mediaplayer.h>
#include <video/mediaplayerbridge.h>

#include <core/resourceview.h>
#include <core/resource.h>
#include <core/optiontoolbuttons.h>
#include <core/resourcepackage.h>
#include <core/resourcepage.h>
#include <core/toolbutton.h>
#include <views/whitecanvas.h>
#include <views/whitecanvaswidget.h>
#include <showboard.h>
#include <video/videocontroller.h>

#include <qcomponentfactory.h>

#include <QMediaService>
#include <QWindow>

static constexpr char const * toolstr =
        "play()|播放|NeedUpdate,Checkable|;"
        "seek()|拖动||;"
        "playRate||OptionsGroup,Popup,NeedUpdate|;"
        "fullScreen()|全屏|;"
        "stop()|停止|;";

VideoControl::VideoControl(ResourceView * res)
    : WidgetControl(res, {
                    WithSelectBar,
                    ExpandScale,
                    KeepAspectRatio,
                    LayoutScale,
                    Touchable,
                    FixedOnCanvas,
                    DelayApplySize}, {CanRotate})
    , playerBridge_(nullptr)
    , player_(nullptr)
    , controller_(nullptr)
    , fullScreenWidget_(nullptr)
    , autoPlay_(false)
{
#ifdef QT_DEBUG
    setToolsString(toolstr);
#else
    (void) toolstr;
#endif
    playerBridge_ = MediaPlayerBridge::get(res_->property("playerimpl").toByteArray());
}

VideoControl::~VideoControl()
{
    if (fullScreenWidget_)
        delete fullScreenWidget_;
}

bool VideoControl::isFullScreen() const
{
    return res_->url() == QUrl("video:full");
}

bool VideoControl::autoPlay() const
{
    return autoPlay_;
}

void VideoControl::setAutoPlay(bool autoPlay)
{
    autoPlay_ = autoPlay;
    emit autoPlayChanged();
}

QObject *VideoControl::player() const
{
    return player_;
}

QVariant VideoControl::controller() const
{
    if (controller_)
        return QVariant::fromValue(controller_);
    return res_->property("controller");
}

void VideoControl::setController(const QVariant &c)
{
    delete controller_;
    controller_ = nullptr;
    if (auto ct = c.value<QWidget*>()) {
        controller_ = ct;
    } else {
        static QComponentFactory<VideoController> factory(ShowBoard::containter());
        controller_ = factory.get(c.toByteArray());
    }
}

QWidget *VideoControl::createWidget(ControlView *parent)
{
    Q_UNUSED(parent)
    QWidget * surface = playerBridge_->createSurface();
    surface->resize(640, 360);
    return surface;
}

void VideoControl::attached()
{
    player_ = res_->property("player").value<QObject*>();
    if (!player_) {
        player_ = playerBridge_->createPlayer();
        player_->setParent(this);
    }
    player_->setProperty("surface", QVariant::fromValue(widget_));
    if (!isFullScreen()) {
        player_->setProperty("position",
                             res_->property("position"));
        connect(player_, SIGNAL(playStateChanged()),
                this, SLOT(playStateChanged()));
        player_->setProperty("source", res_->resource()->url());
    } else {
        loadFinished(true);
        // 暂停情况下截图，fix全屏黑屏
        if (isFullScreen() && player_->property("playState").toInt() == MediaPlayer::State::PausedState){
            player_->setProperty("playState", MediaPlayer::State::PlayingState);
            player_->setProperty("playState", MediaPlayer::State::PausedState);
        }
    }
    if (controller_) {
        controller_->setParent(widget_);
        bindTouchEventToChild(controller_);
    }
}

void VideoControl::detaching()
{
    delete controller_;
    controller_ = nullptr;
    res_->setProperty("position", player_->property("position"));
    if (!isFullScreen()) {
        player_->setProperty("surface", QVariant());
        player_->setProperty("playState", static_cast<int>(MediaPlayer::StoppedState));
        delete player_;
    }
    player_ = nullptr;
}

void VideoControl::fullScreen(bool)
{
    if (!flags_.testFlag(LoadFinished))
        return;
    if (isFullScreen()) {
        QTimer::singleShot(0, this, [this] () {
            VideoControl * another = qobject_cast<VideoControl*>(player_->parent());
            ResourcePackage *pkgage =  qobject_cast<WhiteCanvasWidget*>(another->fullScreenWidget_)->package();
            pkgage->removePage(res_->page());
            another->player_->setProperty("surface", QVariant::fromValue(another->widget()));
            another->fullScreenWidget_->hide();
        });
        return;
    }
    WhiteCanvasWidget * widget = qobject_cast<WhiteCanvasWidget*>(fullScreenWidget_);
    if (widget == nullptr) {
        widget = new WhiteCanvasWidget(WhiteCanvasWidget::mainInstance()->window());
        widget->setWindowFlag(Qt::Tool);
        widget->setAttribute(Qt::WA_NativeWindow);
        widget->windowHandle()->setSurfaceType(QSurface::RasterSurface);
        widget->setResourcePackage(new ResourcePackage(widget));
        widget->scene()->setBackgroundBrush(Qt::black);
        fullScreenWidget_ = widget;
    }
    widget->show();

    widget->package()->newPage(QUrl("video:full"), {
                                   {"playerimpl", res_->property("playerimpl")},
                                   {"controller", res_->property("controller")},
                                   {"deletable", false},
                                   {"pageMode", ResourceView::Independent},
                                   {"scaleMode", FullLayout},
                                   {"player", QVariant::fromValue(player_)}
                               });
}

void VideoControl::play()
{
    int state = player_->property("playState").toInt();
    if (state == MediaPlayer::PlayingState)
        state = MediaPlayer::PausedState;
    else
        state = MediaPlayer::PlayingState;
    player_->setProperty("playState", state);
}

void VideoControl::seek()
{
    player_->setProperty("position", player_->property("position").toInt() + 10000);
}

void VideoControl::stop()
{
    player_->setProperty("playState", static_cast<int>(MediaPlayer::StoppedState));
}

void VideoControl::fullScreen()
{
    fullScreen(true);
}

void VideoControl::updateToolButton(ToolButton *button)
{
    if (button->name() == "play()") {
        int state = player_->property("playState").toInt();
        bool playing = state == MediaPlayer::PlayingState;
        button->setChecked(playing);
        button->setText(playing ? "暂停" : "播放");
    }
    Control::updateToolButton(button);
}

void VideoControl::playStateChanged()
{
    buttonsChanged();
    if (flags_.testFlag(LoadFinished)
            || player_->property("playState").toInt() != MediaPlayer::State::PreparedState)
        return;
    QSize size = player_->property("videoSize").toSize();
    if (!size.isEmpty())
        resize(size);
    loadFinished(true);
}

class PlayRateOptionButtons : public OptionToolButtons
{
public:
    PlayRateOptionButtons()
        : OptionToolButtons(QList<qreal>{2, 1.5, 1.25, 1, 0.75, 0.5}, 1)
    {
    }

protected:
    QString buttonTitle(const QVariant &value) override
    {
        return QString("X ") + value.toString();
    }
};

static PlayRateOptionButtons playRateButtons;

REGISTER_OPTION_BUTTONS(VideoControl, playRate, playRateButtons)
