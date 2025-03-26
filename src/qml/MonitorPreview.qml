import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Item {
    id: preview
    width: 600
    height: 500

    Rectangle {
        anchors.fill: parent
        color: "#222"
        radius: 10

        Repeater {
            model: monitors

            Rectangle {
                width: 150
                height: 100
                x: modelData.positionX
                y: modelData.positionY
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
                        modelData.positionX = parent.x
                        modelData.positionY = parent.y
                    }
                }
            }
        }
    }
}
