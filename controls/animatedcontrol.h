#ifndef ANIMATEDCONTROL_H
#define ANIMATEDCONTROL_H

#include <core/control.h>

class QMovie;

class AnimatedControl : public Control
{
    Q_OBJECT

    Q_PROPERTY(int speed READ speed WRITE setSpeed)

public:
    Q_INVOKABLE AnimatedControl(ResourceView * res);

public slots:
    void play();

    void stop();

    void step();

public:
    int speed() const;

    void setSpeed(int speed);

private:
    ControlView * create(ControlView *parent) override;

    void attached() override;

    void onStream(QIODevice *stream) override;

    void detaching() override;

    void updateToolButton(ToolButton * button) override;

private:
    QMovie * movie_;
};

#endif // ANIMATEDCONTROL_H
