#ifndef SCHEDULEDATAOBJECT_H
#define SCHEDULEDATAOBJECT_H

#include <QObject>

class ScheduleDataObject : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString description READ description WRITE setDescription NOTIFY descriptionChanged)
    Q_PROPERTY(QString startDate READ startDate WRITE setStartDate NOTIFY startDateChanged)
    Q_PROPERTY(QString endDate READ endDate WRITE setEndDate NOTIFY endDateChanged)

    QString description_;
    QString startDate_;
    QString endDate_;

public:
    explicit ScheduleDataObject(QObject *parent = 0);
    ScheduleDataObject(const QString& decsription, const QString& startDate, const QString& endDate);

    QString description();
    void setDescription(const QString& description);
    QString startDate();
    void setStartDate(const QString& startDate);
    QString endDate();
    void setEndDate(const QString& endDate);

signals:
    void descriptionChanged();
    void startDateChanged();
    void endDateChanged();
};

#endif // SCHEDULEDATAOBJECT_H
