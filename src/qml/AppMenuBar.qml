import QtQuick
import QtQuick.Controls

MenuBar {
    Menu {
        title: qsTr("&Menu")
        Action { text: qsTr("&Quit") }
    }
    Menu {
        title: qsTr("&Actions")
        Action { text: qsTr("&Rescan") }
    }
    Menu {
        title: qsTr("&Help")
        Action { text: qsTr("&About") }
    }
}

