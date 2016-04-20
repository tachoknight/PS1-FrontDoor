#ifndef BANNERTIMER_H
#define BANNERTIMER_H

#include <QObject>
#include <QDebug>

class BannerTimer : public QObject
{
    Q_OBJECT

     int timerId;
public:
    explicit BannerTimer(QObject *parent = 0);

signals:
     void showSomething(const QString textToShow, const int randX, const int randY);
public slots:

protected:
    void timerEvent(QTimerEvent *event);
};

#endif // BANNERTIMER_H
