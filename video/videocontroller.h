#ifndef VIDEOCONTROLLER_H
#define VIDEOCONTROLLER_H

#include <QQuickWidget>

class Control;

class VideoController : public QQuickWidget
{
    Q_OBJECT
    Q_PROPERTY(bool enableFeedBack READ enableFeedBack CONSTANT)

public:
    Q_INVOKABLE VideoController(QWidget * parent = nullptr);

    bool enableFeedBack() const;

public slots:
    void feedback(QPointF locationFromRoot);

protected:
    void sizeChanged();

    Control *control();

private:
    virtual bool event(QEvent *event) override;

    virtual bool eventFilter(QObject * watched, QEvent * event) override;
};

#endif // VIDEOCONTROLLER_H
