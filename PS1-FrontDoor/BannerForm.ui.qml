import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1

Rectangle {
    id: rectangle1
    width: 480
    height: 272

    property alias text1: text1


    Image {
        id: image1
        x: 0
        y: 0
        width: 480
        height: 272
        fillMode: Image.PreserveAspectFit
        source: "qrc:/images/ps1-full.jpg"
    }

    Text {
        id: text1
        width: 421
        height: 48
        font.pixelSize: 20
        color: "black"
        font.bold: true

    }
}
