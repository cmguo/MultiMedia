#ifndef AUDIOPLAYERBAR_H
#define AUDIOPLAYERBAR_H

#include "volumebar.h"

#include <QQuickWidget>

class AudioPlayerBar : public QQuickWidget
{
    Q_OBJECT

    Q_PROPERTY(QUrl mediaUrl READ mediaUrl WRITE setMediaUrl NOTIFY mediaUrlChanged)
    Q_PROPERTY(QString mediaTitle READ mediaTitle WRITE setMediaTitle NOTIFY mediaTitleChanged)
    Q_PROPERTY(bool canResize READ canResize WRITE setCanResize NOTIFY canResizeChanged)

public:
    AudioPlayerBar(QWidget *parent = nullptr);

    QUrl mediaUrl() const;
    void setMediaUrl(QUrl url);

    QString mediaTitle() const;
    void setMediaTitle(QString title);

    bool canResize() const;
    void setCanResize(bool b);


    bool closable() const;
    void setClosable(bool b);

signals:
    void mediaUrlChanged();
    void mediaTitleChanged();
    void canResizeChanged();
    void showVolumeBarChanged();
    void volumeChanged();
    void closeSignal();

public slots:
    /// 点击音量
    void volumeClick();
    // 关闭按钮点击
    void closeClick();
    //
    void checkAndHideVolume();

protected:
    void resizeEvent(QResizeEvent *event) override;

private:
    /// 计算QuickItem相对于当前Widget的Geometry
    QRect itemGeometry(QString objectName);
    void initItemGeometry();

private:
    QUrl mMediaUrl;
    QString mMediaTitle;

    bool mClosable {true};

    bool mCanResize { true };

    QRect mPlayerBarRect;
    QRect mSeekBarRect;
    QRect mVolumeButtonRect;

    bool mIsDrag { false };
    QPoint mCurrentMousePoint {0, 0};

    VolumeBar *mVolumeBar;
};

#endif // AUDIOPLAYERWIDGET_H
