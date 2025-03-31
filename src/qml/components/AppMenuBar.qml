import QtQuick
import QtQuick.Controls

MenuBar {
    Menu {
        title: qsTr("&Menu")
        Action { text: qsTr("&Quit") }
    }
    Menu {
        title: qsTr("&Actions")
        Action {
            text: qsTr("&Apply")
            onTriggered: {
                monitorManager.applyMonitorConfiguration()
                window.showConfirmDialog()
            }
        }
        Action {
            text: qsTr("&Rescan")
            onTriggered: monitorManager.scanMonitors()
        }
    }
    Menu {
        title: qsTr("&Help")
        Action { text: qsTr("&About") }
    }
}

