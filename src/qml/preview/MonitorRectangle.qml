import QtQuick
import QtQuick.Controls

Item {
    id: monitorItem

    property var monitor // modelData
    property real canvasWidth
    property real canvasHeight
    property real positionScale
    property real sizeScale
    property bool isDragging: false

    width: monitor.width * sizeScale
    height: monitor.height * sizeScale

    Binding {
        target: monitorItem
        property: "x"
        when: !isDragging
        value: (canvasWidth / 2) + (monitor.positionX * positionScale)
    }

    Binding {
        target: monitorItem
        property: "y"
        when: !isDragging
        value: (canvasHeight / 2) + (monitor.positionY * positionScale)
    }

    Rectangle {
        anchors.fill: parent
        color: monitor.focused ? "deepskyblue" : "lightgray"
        border.color: "white"
        border.width: 2
        radius: 6

        Text {
            anchors.centerIn: parent
            color: "black"
            text: monitor.name
        }
    }

    MouseArea {
        anchors.fill: parent
        drag.target: monitorItem
        drag.axis: Drag.XAndYAxis

        onPressed: {
            monitorManager.selectedMonitor = monitor
        }

        onPositionChanged: {
            const snappedPoint = monitorManager.getSnappedPosition(monitor.name)

            // Update monitor data
            monitor.positionX = snappedPoint.x
            monitor.positionY = snappedPoint.y

            // Force the item to follow the snapped position immediately
            monitorItem.x = (canvasWidth / 2) + (snappedPoint.x * positionScale)
            monitorItem.y = (canvasHeight / 2) + (snappedPoint.y * positionScale)
        }
    }

}

