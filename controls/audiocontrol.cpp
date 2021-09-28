#include "audiocontrol.h"
#include "audio/audioplayerbar.h"

#include <core/resourceview.h>

#include <QTimer>

AudioControl::AudioControl(ResourceView *res)
    : WidgetControl(res, Control::None, Control::CanSelect | Control::CanScale | Control::CanRotate)
{
}

QWidget *AudioControl::createWidget(ControlView *parent)
{
    Q_UNUSED(parent)
    AudioPlayerBar *bar = new AudioPlayerBar;
    bar->setClosable(false);

    connect(bar, &AudioPlayerBar::closeSignal, this, [this]() {
        QTimer::singleShot(200, [this]() {
            this->res_->removeFromPage();
        });
    });
    return bar;
}

void AudioControl::attached()
{
    AudioPlayerBar *bar = qobject_cast<AudioPlayerBar*>(widget_);
    bar->setMediaTitle(res_->property("name").toString());
    bar->setMediaUrl(res_->url());
    loadFinished(true);
}
