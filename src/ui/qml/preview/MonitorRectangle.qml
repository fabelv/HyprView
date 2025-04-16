import QtQuick
import Core 1.0
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

            // Optional: anchor center stays center even after rotation
            transformOrigin: Item.Center

            rotation: {
                switch (monitor?.transform_) {
                case TransformHelper.Rotate90:
                case TransformHelper.FlippedRotate90:
                    return 90;
                case TransformHelper.Rotate180:
                case TransformHelper.FlippedRotate180:
                    return 180;
                case TransformHelper.Rotate270:
                case TransformHelper.FlippedRotate270:
                    return 270;
                default:
                    return 0;
                }
            }

            transform: Scale {
                xScale: (monitor?.transform_ === TransformHelper.Flipped ||
                         monitor?.transform_ === TransformHelper.FlippedRotate90 ||
                         monitor?.transform_ === TransformHelper.FlippedRotate180 ||
                         monitor?.transform_ === TransformHelper.FlippedRotate270) ? -1 : 1
                yScale: 1
            }
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
        const newX = Math.round((monitorItem.x - xOffset) / scaleFactor)
        const newY = Math.round((monitorItem.y - yOffset) / scaleFactor)

        const snappedPos = monitorManager.getSnappedPosition(monitor.name_, Math.round(newX), Math.round(newY))

        monitor.positionX_ = Math.round(snappedPos.x)
        monitor.positionY_ = Math.round(snappedPos.y)

        monitor.positionUpdatedByDragAndDrop()
    }
        }
    }
}

