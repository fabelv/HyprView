import QtQuick.Controls

MenuBar {

    Menu {
        title: qsTr("&Menu")
        objectName: "menuFile"

        Action {
            text: qsTr("&Quit")
            objectName: "actionQuit"
            // Exits the application
            onTriggered: Qt.quit()
        }
    }

    Menu {
        title: qsTr("&Actions")
        objectName: "menuActions"

        Action {
            text: qsTr("&Apply")
            objectName: "actionApply"
            // Applies monitor configuration and opens a confirmation dialog
            onTriggered: {
                monitorManager.applyMonitorConfiguration()
                window.showConfirmDialog()
            }
        }

        Action {
            text: qsTr("&Rescan")
            objectName: "actionRescan"
            // Rescans and reloads connected monitors
            onTriggered: monitorManager.scanMonitors()
        }
    }

    Menu {
        title: qsTr("&Help")
        objectName: "menuHelp"

        Action {
            text: qsTr("&About")
            objectName: "actionAbout"
            // Opens the GitHub repository in the system's default browser
            onTriggered: Qt.openUrlExternally("https://github.com/fabelv/HyprView")
        }
    }
}

