import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Dialogs 1.2
import BannerTimer 1.0

BannerForm {
    width: 480
    height: 272

    BannerTimer {
        id: bannerTimer

        onShowSomething: {
            console.info(randX + " " + randY);
            bannerForm.text1.x = randX;
            bannerForm.text1.y = randY;
            bannerForm.text1.text = textToShow;
        }
    }

    BannerForm {
        id: bannerForm
        anchors.fill: parent
    }
}
