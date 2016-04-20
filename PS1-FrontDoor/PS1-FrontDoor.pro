TEMPLATE = app

QT += qml quick widgets sql network

CONFIG += c++11

SOURCES += main.cpp \
    carouseltimer.cpp \
    bannertimer.cpp \
    scheduletimer.cpp \
    scheduledataobject.cpp

RESOURCES += qml.qrc

# Database file
databases.files = ./events.db
osx:databases.path = "Contents/Resources"

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

DISTFILES += \
    images/ps1-full.jpg \
    URLBannerForm.ui.qml \
    URLBanner.qml \
    images/ps1-logo.jpg

HEADERS += \
    carouseltimer.h \
    bannertimer.h \
    scheduletimer.h \
    scheduledataobject.h
