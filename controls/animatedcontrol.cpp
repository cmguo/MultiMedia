#include "animatedcontrol.h"

#include <core/optiontoolbuttons.h>
#include <core/resourceview.h>
#include <core/toolbutton.h>

#include <QGraphicsPixmapItem>
#include <QMovie>

static char const * toolstr =
        "play()||NeedUpdate,Checkable|:/multimedia/image/ic_media_play.png,normal=,+normal=/ic_media_pause;"
        "speed||Popup,OptionsGroup,NeedUpdate|;"
        "step()|下一帧;"
        "stop()|停止";

AnimatedControl::AnimatedControl(ResourceView * res)
    : Control(res, {KeepAspectRatio, FullSelect, FixedOnCanvas})
{
    setToolsString(toolstr);
    QMovie * movie = new QMovie(this);
    movie->setCacheMode(QMovie::CacheAll);
    movie_ = movie;
}

void AnimatedControl::play()
{
    switch (movie_->state()) {
    case QMovie::NotRunning:
        movie_->start();
        break;
    case QMovie::Running:
        movie_->setPaused(true);
        break;
    case QMovie::Paused:
        movie_->setPaused(false);
        break;
    }
}

void AnimatedControl::stop()
{
    movie_->stop();
    raiseButtonsChanged();
}

void AnimatedControl::step()
{
    movie_->jumpToNextFrame();
}

int AnimatedControl::speed() const
{
    return movie_->speed();
}

void AnimatedControl::setSpeed(int speed)
{
    movie_->setSpeed(speed);
}

ControlView *AnimatedControl::create(ControlView *parent)
{
    (void)parent;
#ifdef SHOWBOARD_QUICK
    return nullptr;
#else
    QGraphicsPixmapItem * item = new QGraphicsPixmapItem;
    item->setShapeMode(QGraphicsPixmapItem::BoundingRectShape);
    item->setTransformationMode(Qt::SmoothTransformation);
    return item;
#endif
}

void AnimatedControl::attached()
{
    loadStream();
}

void AnimatedControl::onStream(QIODevice *stream)
{
    stream->setParent(movie_);
    movie_->setDevice(stream);
    QGraphicsPixmapItem * item = static_cast<QGraphicsPixmapItem*>(item_);
    connect(movie_, &QMovie::updated, this, [item, movie = movie_] () {
        item->setPixmap(movie->currentPixmap());
    });
    movie_->jumpToFrame(0);
}

void AnimatedControl::detaching()
{
    movie_->stop();
}

void AnimatedControl::updateToolButton(ToolButton *button)
{
    if (button->name() == "play()") {
        button->setChecked(movie_ && movie_->state() == QMovie::Running);
    } else {
        Control::updateToolButton(button);
    }
}

class SpeedButtons : public OptionToolButtons
{
public:
    SpeedButtons()
        : OptionToolButtons({25, 50, 100, 200, 400}, 1)
    {
    }

protected:
    QString buttonTitle(const QVariant &value) override
    {
        if (value.toInt() < 100) {
            return "1/" + QString::number(100 / value.toInt());
        } else {
            return "X" + QString::number(value.toInt() / 100);
        }
    }
};

static SpeedButtons speedButtons;

REGISTER_OPTION_BUTTONS(AnimatedControl, speed, speedButtons)
