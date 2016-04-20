import QtQuick 2.4
import ScheduleTimer 1.0

EventScheduleForm {
    width: 480
    height: 272

    EventScheduleForm {
        id: eventScheduleForm
        anchors.fill: parent
    }

    ScheduleTimer {
        id: scheduleTimer

        onShowData: {
            eventScheduleForm.eventListView.model = schedule;
        }
    }

    Component {
        id: eventDelegate
        Item {
            width: 480; height: 60
            Column {
                Text { text: '<b>' + model.modelData.description + '</b>' }
                Text { text: model.modelData.startDate}
            }
        }
    }

    eventListView.onCountChanged: {
        var newIndex = count - 1; // last index
        positionViewAtEnd();
        currentIndex = newIndex;
        console.info("count changed to " + newIndex);
    }
}
