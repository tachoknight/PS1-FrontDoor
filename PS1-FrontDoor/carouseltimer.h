#ifndef CAROUSELTIMER_H
#define CAROUSELTIMER_H

#include <QObject>
#include <QDebug>

const int EVENT_SCREEN_LOOP_COUNT = 10;

class CarouselTimer : public QObject
{
    Q_OBJECT

    int timerId;
    int currentScreen;

    // We want to show the event screen longer than
    // the other screens, so we're going to keep
    // a count of how many times we've looped and use
    // this variable to keep the event screen going
    // longer than the others
    int eventScreenCount;

public:
    explicit CarouselTimer(QObject *parent = 0);

signals:
    void switchState(const QString newState);
public slots:

protected:
    void timerEvent(QTimerEvent *event);
};

#endif // CAROUSELTIMER_H
