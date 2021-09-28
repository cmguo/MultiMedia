#ifndef VOLUMEBAR_H
#define VOLUMEBAR_H

#include <QQuickWidget>

class VolumeBar : public QQuickWidget
{
    Q_OBJECT

    Q_PROPERTY(double volume READ volume WRITE setVolume NOTIFY volumeChanged)
    Q_PROPERTY(bool upDown MEMBER mUpDown NOTIFY changed)

public:
    VolumeBar(QWidget *parent = nullptr);

    double volume() const;
    void setVolume(double v);

    bool upDown() const;
    void setUpDown(bool upDown);

    bool event(QEvent *) override;

signals:
    void volumeChanged();
    void changed();

private:
    double mVolume {1.0};
    bool mUpDown = false;
    bool timerCancelFlag_ = false;

};

#endif // VOLUMEBAR_H
