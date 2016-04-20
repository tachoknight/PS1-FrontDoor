#ifndef SCHEDULETIMER_H
#define SCHEDULETIMER_H

#include <QObject>
#include <QDebug>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>

#include <vector>
using std::vector;

#include "scheduledataobject.h"

class ScheduleTimer : public QObject
{
    Q_OBJECT

    struct Event
    {
        QString description;
        QString startDate;
        QString endDate;
        unsigned long startEpoch;
        unsigned long endEpoch;
    };

    vector<Event> events;

    int timerId;

    // For working with the remote server
    QUrl url;
    QNetworkAccessManager networkAccessMgr;

public:
    explicit ScheduleTimer(QObject *parent = 0);

signals:
    void showData(const QList<QObject*>& schedule);
private slots:
    void gotScheduleData(QNetworkReply* reply);
public slots:

protected:
    void timerEvent(QTimerEvent *event);

private:
    void transformJson(const QByteArray &responseJson);
    void getSchedule();
};

#endif // SCHEDULETIMER_H
