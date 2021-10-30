#ifndef VECTORCONTROL_H
#define VECTORCONTROL_H

#include <core/control.h>

class VectorControl : public Control
{
    Q_OBJECT
public:
    Q_INVOKABLE VectorControl(ResourceView * res);

private:
    ControlView * create(ControlView *parent) override;

    void attached() override;

    void onData(QByteArray data) override;
};

#endif // VECTORCONTROL_H
