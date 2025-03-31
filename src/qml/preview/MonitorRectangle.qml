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

        onPressed: {
            isDragging = true
            monitorManager.selectedMonitor = monitor
        }

        onReleased: {
            let newX = Math.max(0, Math.min(monitorItem.x, canvasWidth - monitorItem.width))
            let newY = Math.max(0, Math.min(monitorItem.y, canvasHeight - monitorItem.height))

            monitorItem.x = newX
            monitorItem.y = newY

            const virtX = (newX - canvasWidth / 2) / positionScale
            const virtY = (newY - canvasHeight / 2) / positionScale

            if (monitor) {
                monitor.positionX = Math.round(virtX)
                monitor.positionY = Math.round(virtY)
            }

            Qt.callLater(() => isDragging = false)
        }
    }
}

