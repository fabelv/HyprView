import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Dialogs

ApplicationWindow {
    id: window
    visible: true
    width: 1200 
    height: 600
    title: "HyprView"

        property int confirmTimeout: 15
    property int countdown: confirmTimeout

    Timer {
        id: revertTimer
        interval: 1000
        running: false
        repeat: true
        onTriggered: {
            countdown--
            if (countdown <= 0) {
                revertTimer.stop()
                confirmDialog.close()
                monitorManager.revertAplly()
            } else {
                confirmDialog.title = `Keep this configuration? (${countdown}s)`
            }
        }
    }

    Dialog {
        id: confirmDialog
        modal: true
        title: `Keep this configuration? (${countdown}s)`
        standardButtons: Dialog.NoButton

        ColumnLayout {
            spacing: 10
            Label {
                text: "Click 'Yes' to keep this configuration. If you do nothing, it will be reverted in 15 seconds."
                wrapMode: Text.Wrap
            }

            RowLayout {
                spacing: 10
                Button {
                    text: "Yes"
                    onClicked: {
                        revertTimer.stop()
                        confirmDialog.close()
                    }
                }
                Button {
                    text: "No"
                    onClicked: {
                        revertTimer.stop()
                        confirmDialog.close()
                        monitorManager.revertAplly()
                    }
                }
            }
        }
    }

    // Show the dialog and start the timer when Apply is clicked
    function showConfirmDialog() {
        countdown = confirmTimeout
        confirmDialog.title = `Keep this configuration? (${countdown}s)`
        confirmDialog.open()
        revertTimer.start()
    }

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
                onClicked: {
                    monitorManager.apply()
                    window.showConfirmDialog()
                }
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

