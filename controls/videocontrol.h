#ifndef VIDEOCONTROL_H
#define VIDEOCONTROL_H

#include <controls/widgetcontrol.h>

#include <QVariant>

class MediaPlayerBridge;

class VideoControl : public WidgetControl
{
    Q_OBJECT
    Q_PROPERTY(QObject *player READ player CONSTANT)
    Q_PROPERTY(QVariant controller READ controller WRITE setController)
    Q_PROPERTY(bool fullScreen READ isFullScreen WRITE fullScreen NOTIFY fullScreenChanged)
    Q_PROPERTY(bool autoPlay READ autoPlay WRITE setAutoPlay NOTIFY autoPlayChanged)

public:
    Q_INVOKABLE VideoControl(ResourceView *res);

    virtual ~VideoControl() override;

public:
    bool isFullScreen() const;

    void fullScreen(bool);

    bool autoPlay()const;

    void setAutoPlay(bool autoPlay);

    QObject *player() const;

    QVariant controller() const;

    void setController(QVariant const & c);

Q_SIGNALS:
    void fullScreenChanged();

    void autoPlayChanged();

public slots:
    void play();

    void seek();

    void stop();

    void fullScreen();

protected:

    virtual QWidget * createWidget(ControlView * parent) override;

    virtual void attached() override;

    virtual void detaching() override;

    virtual void updateToolButton(ToolButton *button) override;

private slots:
    void playStateChanged();

private:
    MediaPlayerBridge * playerBridge_;
    QObject * player_;
    QWidget * controller_;
    QWidget * fullScreenWidget_;
    bool autoPlay_;
};

#endif // VIDEOCONTROL_H
