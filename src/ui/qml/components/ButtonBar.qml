import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

RowLayout {
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
