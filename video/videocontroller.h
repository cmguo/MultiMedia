#ifndef VIDEOCONTROLLER_H
#define VIDEOCONTROLLER_H

#include <QQuickWidget>

class Control;

class VideoController : public QQuickWidget
{
    Q_OBJECT
public:
    Q_INVOKABLE VideoController(QWidget * parent = nullptr);

protected:
    void sizeChanged();

    Control *control();

private:
    virtual bool event(QEvent *event) override;

    virtual bool eventFilter(QObject * watched, QEvent * event) override;
};

#endif // VIDEOCONTROLLER_H
