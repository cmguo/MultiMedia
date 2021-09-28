#ifndef AUDIOCONTROL_H
#define AUDIOCONTROL_H

#include <controls/widgetcontrol.h>

class AudioControl : public WidgetControl
{
    Q_OBJECT
public:
    Q_INVOKABLE AudioControl(ResourceView *res);


protected:
    virtual QWidget * createWidget(ControlView * parent) override;

    virtual void attached() override;
};

#endif // AUDIOCONTROL_H
