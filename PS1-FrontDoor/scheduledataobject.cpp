#include "scheduledataobject.h"

ScheduleDataObject::ScheduleDataObject(QObject *parent) : QObject(parent)
{

}

ScheduleDataObject::ScheduleDataObject(const QString& description, const QString& startDate, const QString& endDate)
{
    setDescription(description);
    setStartDate(startDate);
    setEndDate(endDate);
}

void ScheduleDataObject::setDescription(const QString& description)
{
    this->description_ = description;
}

void ScheduleDataObject::setStartDate(const QString& startDate)
{
    this->startDate_ = startDate;
}

void ScheduleDataObject::setEndDate(const QString& endDate)
{
    this->endDate_ = endDate;
}

QString ScheduleDataObject::description()
{
    return this->description_;
}

QString ScheduleDataObject::startDate()
{
    return this->startDate_;
}

QString ScheduleDataObject::endDate()
{
    return this->endDate_;
}
