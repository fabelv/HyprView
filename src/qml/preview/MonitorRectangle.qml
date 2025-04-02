
import QtQuick
import QtQuick.Controls

Item {
    id: monitorItem

    property var monitor

    x: monitor.positionX
    y: monitor.positionY
    width: monitor.width
    height: monitor.height

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

    MouseArea {
        anchors.fill: parent
        drag.target: monitorItem

        onPressed: monitorManager.selectedMonitor = monitor

        onPositionChanged: {
            monitor.positionX = monitorItem.x
            monitor.positionY = monitorItem.y
        }
    }
}

