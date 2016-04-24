#include "scheduletimer.h"

ScheduleTimer::ScheduleTimer(QObject *parent) : QObject(parent), networkAccessMgr(this)
{   
    qInfo() << "Starting schedule timer...";

    // 1000 == 1 second
    // This sets the timer to run every 30 minutes
    timerId = startTimer((1000 * 60) * 30);

    // Connect the finished signal to our slot which gets the response
    connect(&networkAccessMgr, SIGNAL(finished(QNetworkReply*)), this, SLOT(gotScheduleData(QNetworkReply*)));

    // Start by filling the list before the timer gets to it
    getSchedule();
}

void ScheduleTimer::transformJson(const QByteArray &responseJson)
{
    QJsonDocument jsonDoc = QJsonDocument::fromJson(responseJson);
    QJsonArray jsonArray = jsonDoc.array();

    bool resetList = true;

    foreach (const QJsonValue & value, jsonArray)
    {
        QJsonObject obj = value.toObject();

        Event newEvent;
        newEvent.description = obj["description"].toString();
        newEvent.startDate = obj["startDate"].toString();
        newEvent.endDate = obj["endDate"].toString("");
        newEvent.startEpoch = obj["startEpoch"].toVariant().toLongLong();
        newEvent.endEpoch = obj["endEpoch"].toVariant().toLongLong();

        if (resetList)
        {
            // Clear out the old list of events
            events.clear();
            resetList = false;
        }

        events.push_back(newEvent);
    }

    std::sort(events.begin(), events.end(),
              [](const Event& lhs, const Event& rhs) -> bool
    {
        return lhs.startEpoch < rhs.startEpoch;
    });
}

void ScheduleTimer::timerEvent(QTimerEvent *event)
{
    qInfo() << "In the schedule timer event...";

    getSchedule();
}

void ScheduleTimer::getSchedule()
{
    // the HTTP request
    QNetworkRequest req(QUrl("http://10.100.0.49:8080/doorman/ps1schedule"));

    // And do the actual request...
    networkAccessMgr.get(req);
}

void ScheduleTimer::gotScheduleData(QNetworkReply* reply)
{
    qInfo() << "Got the signal!";
    reply->deleteLater();

    if (reply->error() == QNetworkReply::NoError)
    {
        // Now let's get our result payload...
        auto responseJson = reply->readAll();

        // And this method will add everything to list and sort it by start time
        transformJson(responseJson);

        // Now we need to turn our STL vector into a QList...
        // XYZZY : Limit to only the first four events so we
        // don't have to scroll
        int count = 0;
        QList<QObject*> eventList;
        foreach(const Event& event, events)
        {
            if (count++ > 4)
                break;

            qInfo() << "Adding " << event.description << " at " << event.startDate;

            eventList.append((QObject*) new ScheduleDataObject(event.description, event.startDate, event.endDate));
        }

        showData(eventList);
    }
    else
    {
        //failure
        qInfo() << "Failure" << reply->errorString();
    }
}
