import QtQuick
import HyprView

Item {
    id: monitorItem

    property var monitor
    property real scaleFactor
    property int xOffset
    property int yOffset

    width: monitor ? monitor.width_ * scaleFactor : 0
    height: monitor ? monitor.height_ * scaleFactor : 0
    x: monitor ? monitor.positionX_ * scaleFactor + xOffset : 0
    y: monitor ? monitor.positionY_ * scaleFactor + yOffset : 0

    Rectangle {
        anchors.fill: parent
        color: monitor?.id_ === monitorManager?.selectedMonitor_?.id_ ? "deepskyblue" : "lightgray"
        border.color: "grey"
        border.width: 2
        radius: 6

        Text {
            anchors.centerIn: parent
            text: monitor?.name_ ?? "N/A"
            color: "black"
        }
    }

    onXChanged: {
        if (dragArea.drag.active && monitor) {
            let newX = (x - xOffset) / scaleFactor
            monitor.positionX_ = Math.round(newX)
        }
    }

    onYChanged: {
        if (dragArea.drag.active && monitor) {
            let newY = (y - yOffset) / scaleFactor
            monitor.positionY_ = Math.round(newY)
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
            monitorManager.setSelectedMonitor(monitor)
        }

        onReleased: {
            cursorShape = Qt.OpenHandCursor

            if (monitor) {
            //    const newX = (x - xOffset) / scaleFactor
            //    const newY = (y - yOffset) / scaleFactor
            //
            //    monitor.positionX_ = Math.round(newX)
            //    monitor.positionY_ = Math.round(newY)
            //
            //    const snappedPos = monitorManager.getSnappedPosition(monitor.name_)
            //    monitor.positionX_ = Math.round(snappedPos.x)
            //    monitor.positionY_ = Math.round(snappedPos.y)
            //
                monitor.positionUpdatedByDragAndDrop()
            }
        }
    }
}

