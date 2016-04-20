#include "carouseltimer.h"

CarouselTimer::CarouselTimer(QObject *parent) : QObject(parent), currentScreen(0), eventScreenCount(0)
{
    qDebug() << "Starting carousel timer...";

    // 1000 == 1 second
    timerId = startTimer(5000);
}

void CarouselTimer::timerEvent(QTimerEvent *event)
{
    qDebug() << "In the carousel timer event...";

    if (currentScreen == 0)
    {
        qInfo() << "....Switching to Banner";
        currentScreen = 1;
        switchState("MainBannerState");
    }
    else if (currentScreen == 1)
    {
        qInfo() << "....Switching to URL Banner";
        currentScreen = 2;
        switchState("URLBannerState");
    }
    else if (currentScreen == 2)
    {
        qInfo() << "....Switching to Event Schedule";

        // Have we shown the event screen enough?
        if (++eventScreenCount > EVENT_SCREEN_LOOP_COUNT)
        {
            // Yes we have, so reset everything
            currentScreen = 0;
            eventScreenCount = 0;
        }

        switchState("EventState");
    }
}
