import QtQuick 2.6
import QtQuick.Controls 1.5
import QtQuick.Dialogs 1.2

Rectangle {
    id: rectangle1
    width: 480
    height: 272

    property alias eventListView: eventListView
    ScrollView {
        anchors.top: text1.bottom
        anchors.topMargin: 6
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 8
        anchors.right: parent.right
        anchors.rightMargin: 8
        anchors.left: parent.left
        anchors.leftMargin: 8
        verticalScrollBarPolicy: Qt.ScrollBarAlwaysOff
        ListView {
            id: eventListView
            delegate: eventDelegate       
        }
    }

    Text {
        id: text1
        x: 156
        y: 8
        text: qsTr("Upcoming Events")
        font.bold: true
        font.pixelSize: 21
    }

    Image {
        id: image1
        antialiasing: true
        sourceSize.height: 35
        sourceSize.width: 35
        fillMode: Image.PreserveAspectFit
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 234
        anchors.top: parent.top
        anchors.topMargin: 3
        anchors.right: text1.left
        anchors.rightMargin: 112
        anchors.left: parent.left
        anchors.leftMargin: 9
        source: "qrc:/images/ps1-logo.png"
    }
}
