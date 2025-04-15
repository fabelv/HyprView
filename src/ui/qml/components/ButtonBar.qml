import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

RowLayout {
    id: buttonBar
    objectName: "buttonBar"

    // Center the buttons horizontally
    Layout.alignment: Qt.AlignHCenter
    spacing: 16

    Button {
        id: applyButton
        text: qsTr("Apply")
        onClicked: monitorManager.applyMonitorConfiguration()
    }

    Button {
        id: rescanButton
        text: qsTr("Rescan")
        onClicked: monitorManager.scanMonitors()
    }
}

