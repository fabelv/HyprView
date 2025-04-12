import QtQuick
import HyprView

Item {
    id: monitorItem

    property var monitor
    property int index: 0
    property real scaleFactor
    property int xOffset
    property int yOffset

    width: monitor ? monitor.width * scaleFactor : 0
    height: monitor ? monitor.height * scaleFactor : 0
    x: monitor ? monitor.positionX * scaleFactor + xOffset : 0
    y: monitor ? monitor.positionY * scaleFactor + yOffset : 0

    Rectangle {
        anchors.fill: parent
        color: index === monitorManager.selectedMonitorIndex_ ? "deepskyblue" : "lightgray"
        border.color: "white"
        border.width: 2
        radius: 6

        Text {
            anchors.centerIn: parent
            text: monitor.name
            color: "black"
        }
    }

    onXChanged: {
        if (dragArea.drag.active) {
            let newX = (monitorItem.x - xOffset) / scaleFactor
            monitor.positionX = Math.round(newX)
        }
    }

    onYChanged: {
        if (dragArea.drag.active) {
            let newY = (monitorItem.y - yOffset) / scaleFactor
            monitor.positionY = Math.round(newY)
        }
    }

    MouseArea {
        id: dragArea
        anchors.fill: parent
        drag.target: monitorItem
        drag.axis: Drag.XAndYAxis
        hoverEnabled: true
        cursorShape: Qt.OpenHandCursor

        onPressed: {
            cursorShape = Qt.ClosedHandCursor
            monitorManager.selectedMonitor = monitor
        }

        onReleased: {
            cursorShape = Qt.OpenHandCursor

            if (monitor) {
                monitor.positionX = Math.round((monitorItem.x - xOffset) / scaleFactor)
                monitor.positionY = Math.round((monitorItem.y - yOffset) / scaleFactor)
                const snappedPos = monitorManager.getSnappedPosition(monitor.name)
                monitor.positionX = Math.round(snappedPos.x)
                monitor.positionY = Math.round(snappedPos.y)

                monitor.positionUpdatedByDragAndDrop()
            }
        }
    }
}

