import QtQuick
import QtQuick.Controls
import QtQuick.Layouts


Item {
    id: preview
    width: 600
    height: 500

    property var monitors
    property var selectedMonitor

    // Define virtual bounds
    property int virtualWidth: 3840
    property int virtualHeight: 2160

    // Scale position to fit layout (but allow big monitors)
    property real positionScale: 0.05     // Tune this
    property real sizeScale: 0.05         // Tune this independently

    Rectangle {
        anchors.fill: parent
        color: "#222"
        radius: 10
        clip: true

        // origin cross (optional)
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
            model: monitors

            Rectangle {
                property real posScale: preview.positionScale
                property real sizeScale: preview.sizeScale

                // Convert logical center-based coords to UI coords
                x: (preview.width / 2) + (modelData.positionX * posScale)
                y: (preview.height / 2) + (modelData.positionY * posScale)

                width: modelData.width * sizeScale
                height: modelData.height * sizeScale

                color: modelData.focused ? "deepskyblue" : "lightgray"
                border.color: "white"
                border.width: 2
                radius: 6

                Text {
                    anchors.centerIn: parent
                    color: "black"
                    text: modelData.name
                }

                MouseArea {
                    anchors.fill: parent
                    drag.target: parent

                    onReleased: {
                        let newX = Math.max(0, Math.min(parent.x, preview.width - parent.width));
                        let newY = Math.max(0, Math.min(parent.y, preview.height - parent.height));

                        parent.x = newX
                        parent.y = newY

                        // Convert UI position back to centered virtual coordinates
                        modelData.positionX = (newX - preview.width / 2) / posScale
                        modelData.positionY = (newY - preview.height / 2) / posScale
                    }
                }
            }
        }
    }
}
