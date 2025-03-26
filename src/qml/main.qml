import QtQuick
import QtQuick.Controls

ApplicationWindow {
    width: 800
    height: 600
    visible: true
    title: qsTr("HyprView (QML)")

    Rectangle {
        anchors.fill: parent
        color: "lightsteelblue"

        Text {
            text: "QML Setup Works 🚀"
            anchors.centerIn: parent
            font.pixelSize: 24
        }
    }
}
