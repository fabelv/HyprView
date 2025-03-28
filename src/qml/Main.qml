import QtQuick
import QtQuick.Controls
import QtQuick.Layouts


ApplicationWindow {
    visible: true
    width: 1200 
    height: 600
    title: "QML Scratch"

    menuBar: AppMenuBar { }

    ColumnLayout {
        anchors.fill: parent

        RowLayout {
            Layout.fillWidth: true
            Layout.fillHeight: true
            spacing: 10

            MonitorPreview {
                Layout.preferredWidth: 0.6 * parent.width
                Layout.fillHeight: true
            }

            MonitorDetails {
                Layout.fillWidth: true
                Layout.fillHeight: true
            }
        }

        RowLayout {
            Layout.alignment: Qt.AlignHCenter
            spacing: 10

            Button {
                text: "Apply"
                onClicked: {
                    console.log("Apply clicked for", selectedMonitor.name)
                }
            }

            Button {
                text: "Rescan"
                onClicked: {
                    console.log("Rescan clicked for", selectedMonitor.name)
                }
            }
        }
    }
}

