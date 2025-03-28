import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ApplicationWindow {
    visible: true
    width: 1200 
    height: 600
    title: "HyprView"

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
                monitors: monitorManager.monitors
                selectedMonitor: monitorManager.selectedMonitor
            }

            MonitorDetails {
                Layout.fillWidth: true
                Layout.fillHeight: true
                selectedMonitor: monitorManager.selectedMonitor
                monitors: monitorManager.monitors
            }
        }

        RowLayout {
            Layout.alignment: Qt.AlignHCenter
            spacing: 10

            Button {
                text: "Apply"
                onClicked: monitorManager.apply()
            }

            Button {
                text: "Rescan"
                onClicked: monitorManager.rescan()
            }
        }
    }

    Component.onCompleted: {
        console.log("=== QML DEBUG ===")
        console.log("monitorManager.monitors:", monitorManager.monitors)
        console.log("monitorManager.selectedMonitor:", monitorManager.selectedMonitor)

        if (monitorManager.selectedMonitor) {
            console.log("selectedMonitor.getName():", monitorManager.selectedMonitor.getName?.())
            console.log("selectedMonitor.getId():", monitorManager.selectedMonitor.getId?.())
        }

        if (monitorManager.monitors) {
            for (let i = 0; i < monitorManager.monitors.length; ++i) {
                const mon = monitorManager.monitors[i];
                console.log(`Monitor[${i}] -> name:`, mon.getName?.(), "id:", mon.getId?.());
            }
        }
    }
}

