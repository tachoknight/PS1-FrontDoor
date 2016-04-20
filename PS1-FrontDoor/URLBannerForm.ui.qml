import QtQuick 2.4

Rectangle {
    id: rectangle1
    width: 480
    height: 272

    property alias text1: text1

    Rectangle {
        id: rectangle2
        x: 0
        y: 0
        width: 480
        height: 272
        gradient: Gradient {
            GradientStop {
                position: 0.426
                color: "#ffffff"
            }

            GradientStop {
                position: 1
                color: "#6c6cef"
            }
        }

        Image {
            id: image1
            antialiasing: true
            anchors.right: parent.right
            anchors.rightMargin: 190
            anchors.left: parent.left
            anchors.leftMargin: 190
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 164
            anchors.top: parent.top
            anchors.topMargin: 8
            fillMode: Image.PreserveAspectFit
            source: "qrc:/images/ps1-logo.png"
        }
    }

    Text {
        id: text1
        x: 69
        y: 83
        width: 411
        height: 56
        color: "#d81212"
        text: qsTr("pumpingstationone.org")
        font.bold: true
        horizontalAlignment: Text.AlignHCenter
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        z: 1
        font.pixelSize: 32
    }


    Text {
        id: text2
        x: 34
        y: 179
        width: 411
        height: 32
        text: qsTr("Open House Every Tuesday at 8pm")
        horizontalAlignment: Text.AlignHCenter
        font.pixelSize: 20
    }
}
