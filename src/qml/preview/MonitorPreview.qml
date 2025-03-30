
import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Item {
    id: preview
    width: 600
    height: 500

    property var monitors
    property var selectedMonitor

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
            model: monitors

            Item {
                id: monitorItem
                property real posScale: preview.positionScale
                property bool isDragging: false

                width: modelData.width * preview.sizeScale
                height: modelData.height * preview.sizeScale

                // Live bindings (disabled when dragging)
                Binding {
                    id: xBinding
                    target: monitorItem
                    property: "x"
                    when: !monitorItem.isDragging
                    value: (preview.width / 2) + (modelData.positionX * posScale)
                }

                Binding {
                    id: yBinding
                    target: monitorItem
                    property: "y"
                    when: !monitorItem.isDragging
                    value: (preview.height / 2) + (modelData.positionY * posScale)
                }

                Rectangle {
                    anchors.fill: parent
                    color: modelData.focused ? "deepskyblue" : "lightgray"
                    border.color: "white"
                    border.width: 2
                    radius: 6

                    Text {
                        anchors.centerIn: parent
                        color: "black"
                        text: modelData.name
                    }
                }

                MouseArea {
                    anchors.fill: parent
                    drag.target: monitorItem

                    onPressed: {
                        monitorItem.isDragging = true
                    }

                    onReleased: {
                        let newX = Math.max(0, Math.min(monitorItem.x, preview.width - monitorItem.width))
                        let newY = Math.max(0, Math.min(monitorItem.y, preview.height - monitorItem.height))

                        monitorItem.x = newX
                        monitorItem.y = newY

                        const virtX = (newX - preview.width / 2) / posScale
                        const virtY = (newY - preview.height / 2) / posScale

                        if (modelData) {
                            modelData.positionX = Math.round(virtX)
                            modelData.positionY = Math.round(virtY)
                        }

                        // Reactivate bindings next frame
                        Qt.callLater(() => {
                            monitorItem.isDragging = false
                        })
                    }
                }
            }
        }
    }
}

