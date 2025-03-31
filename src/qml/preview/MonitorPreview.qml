import QtQuick
import QtQuick.Controls

Item {
    id: preview
    width: 600
    height: 500

    property real positionScale: 0.05
    property real sizeScale: 0.05

    Rectangle {
        anchors.fill: parent
        color: "#222"
        radius: 10
        clip: true

        Rectangle {
            width: 2
            height: parent.height
            color: "white"
            x: parent.width / 2
        }

        Rectangle {
            width: parent.width
            height: 2
            color: "white"
            y: parent.height / 2
        }

        Repeater {
            model: monitorManager.monitors

            MonitorRectangle {
                id: monitorRect
                monitor: modelData
                canvasWidth: preview.width
                canvasHeight: preview.height
                positionScale: preview.positionScale
                sizeScale: preview.sizeScale
            }
        }
    }
}

