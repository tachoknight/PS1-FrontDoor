#include "bannertimer.h"

BannerTimer::BannerTimer(QObject *parent) : QObject(parent)
{
    qDebug() << "Starting banner timer...";

    // 1000 == 1 second
    timerId = startTimer(5000);
}

void BannerTimer::timerEvent(QTimerEvent *event)
{
    qDebug() << "In the banner timer event...";

    srand((unsigned)time(NULL));

    // Screen dimensions are:
    // 480 x 272

    QString response;
    response.sprintf("Open house Tuedays at 8 pm");
    showSomething(response, rand() % 400, rand() % 200);
}
