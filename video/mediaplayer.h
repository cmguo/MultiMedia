#ifndef MEDIAPLAYER_H
#define MEDIAPLAYER_H

#include <QObject>


class MediaPlayer:public QObject
{
    Q_OBJECT
    Q_ENUMS(State)
public:
    enum State {
        IdleState = 0,
        ErrorState,
        PreparedState,
        PlayingState,
        PausedState,
        StoppedState,
    };
public:
    MediaPlayer(QObject *parent = nullptr);
};

#endif // MEDIAPLAYER_H
