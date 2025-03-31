import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

RowLayout {
    spacing: 10
    Layout.alignment: Qt.AlignHCenter

    Button {
        text: "Apply"
        onClicked: monitorManager.applyMonitorConfiguration()
    }

    Button {
        text: "Rescan"
        onClicked: monitorManager.scanMonitors()
    }
}
