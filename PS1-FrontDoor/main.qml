import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Dialogs 1.2
import CarouselTimer 1.0

ApplicationWindow {
    id: appWindow
    visible: true
    title: qsTr("Marquee")
    width: 480
    height: 272

    // These two lines are necessary to make the app full
    // screen with no menu bar
    flags: Qt.SplashScreen
    visibility: Qt.WindowFullScreen

    Rectangle {
        id: rect
        width: parent.width
        height: parent.height


        CarouselTimer {
            id: mainRefresher

            onSwitchState: {
                console.info("Switching to " + newState);
                rect.state = newState;
            }
        }

        // Now let's set up our screens...

        EventSchedule {
            id: eventScheduleForm
            anchors.fill: parent
        }

        URLBanner {
            id: urlBannerForm
            anchors.fill: parent
        }

        // This should be the last form shown because it will
        // be the first one displayed (i.e. it's handled last,
        // which means it's on top of the stack)
        Banner {
            id: bannerForm
            anchors.fill: parent
        }


        states: [
            State {
                name: "MainBannerState"
                PropertyChanges {target: bannerForm; opacity: 1.0}
                PropertyChanges {target: urlBannerForm; opacity: 0.0}
                PropertyChanges {target: eventScheduleForm; opacity: 0.0}
            },
            State {
                name: "URLBannerState"
                PropertyChanges {target: urlBannerForm; opacity: 1.0}
                PropertyChanges {target: bannerForm; opacity: 0.0}
                PropertyChanges {target: eventScheduleForm; opacity: 0.0}
            },
            State {
                name: "EventState"
                PropertyChanges {target: eventScheduleForm; opacity: 1.0}
                PropertyChanges {target: urlBannerForm; opacity: 0.0}
                PropertyChanges {target: bannerForm; opacity: 0.0}
            }
        ]

        // And this is how we do the cross-fade between the screens
        transitions: Transition {
            NumberAnimation {
                property: "opacity"
                duration: 500
                easing.type: Easing.InOutQuad
            }
        }
    }
}
