import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ApplicationWindow {
    visible: true
    width: 1200 
    height: 600
    title: "QML Scratch"

    menuBar: AppMenuBar { }


    RowLayout {
        anchors.fill: parent
        spacing: 10

        MonitorPreview {
            Layout.preferredWidth: parent.width * 0.7
            Layout.fillHeight: true
        }

        MonitorDetails {
            Layout.fillWidth: true
            Layout.fillHeight: true
        }
    }

}

