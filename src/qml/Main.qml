import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ApplicationWindow {
    visible: true
    width: 1000
    height: 600
    title: "HyprView"

    RowLayout {
        anchors.fill: parent
        spacing: 20

        MonitorPreview {
            Layout.preferredWidth: 600
            Layout.fillHeight: true
        }

        //MonitorDetails {
        //    Layout.fillWidth: true
        //    Layout.fillHeight: true
        //}
    }
}

