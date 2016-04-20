#include <QApplication>
#include <QQmlApplicationEngine>
#include <QtQml>

#include "bannertimer.h"
#include "carouseltimer.h"
#include "scheduletimer.h"

int main(int argc, char *argv[])
{
    // Register our C++ classes with QML
    qmlRegisterType<CarouselTimer>("CarouselTimer", 1, 0, "CarouselTimer");
    qmlRegisterType<BannerTimer>("BannerTimer", 1, 0, "BannerTimer");
    qmlRegisterType<ScheduleTimer>("ScheduleTimer", 1, 0, "ScheduleTimer");

    QApplication app(argc, argv);
    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
