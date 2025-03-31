import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Dialog {
    id: confirmDialog
    modal: true
    property int countdown: 0
    property int timeout: 15

    Timer {
        id: revertTimer
        interval: 1000
        running: false
        repeat: true
        onTriggered: {
            confirmDialog.countdown--
            title = `Keep this configuration? (${confirmDialog.countdown}s)`
            if (countdown <= 0) {
                revertTimer.stop()
                close()
                monitorManager.revertMonitorConfiguration()
            }
        }
    }

    function startTimer() {
        countdown = timeout
        title = `Keep this configuration? (${countdown}s)`
        open()
        revertTimer.start()
    }

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
                    close()
                    monitorManager.scanMonitors()
                }
            }
            Button {
                text: "No"
                onClicked: {
                    revertTimer.stop()
                    close()
                    monitorManager.revertMonitorConfiguration()
                }
            }
        }
    }

    Connections {
        target: monitorManager
        function onMonitorConfigurationApplied() {
            confirmDialog.startTimer()
        }
    }
}

