import QtQuick
import QtQuick.Controls

Item {
    id: monitorItem

    property var monitor
    property real scaleFactor

    width: monitor.width * scaleFactor
    height: monitor.height * scaleFactor

    Rectangle {
        anchors.fill: parent
        color: monitor === monitorManager.selectedMonitor ? "deepskyblue" : "lightgray"
        border.color: "white"
        border.width: 2
        radius: 6

        Text {
            anchors.centerIn: parent
            text: monitor.name
            color: "black"
        }
    }
}

