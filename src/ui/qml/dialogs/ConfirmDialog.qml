import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Dialog {
    id: confirmDialog
    objectName: "confirmDialog"
    modal: true

    property int countdown: 0
    property int timeout: 10

    // Center the dialog in the parent window
    x: (parent.width - width) / 2
    y: (parent.height - height) / 2

    title: qsTr("Keep this configuration?")

    function startTimer() {
        countdown = timeout
        title = qsTr("Keep this configuration? (%1s)").arg(countdown)
        open()
        revertTimer.start()
    }

    // Triggered when monitor configuration is applied
    Connections {
        target: monitorManager
        function onMonitorConfigurationApplied() {
            confirmDialog.startTimer()
        }
    }

    Timer {
        id: revertTimer
        interval: 1000
        running: false
        repeat: true

        onTriggered: {
            confirmDialog.countdown--
            title = qsTr("Keep this configuration? (%1s)").arg(confirmDialog.countdown)

            if (confirmDialog.countdown <= 0) {
                revertTimer.stop()
                close()
                // Revert monitor configuration when time runs out
                monitorManager.revertMonitorConfiguration()
            }
        }
    }

    ColumnLayout {
        spacing: 10

        Label {
            // Informational text about the countdown
            text: qsTr("Click 'Yes' to keep this configuration. If you do nothing, it will be reverted in %1 seconds.").arg(confirmDialog.timeout)
            wrapMode: Text.Wrap
        }

        RowLayout {
            spacing: 10

            Button {
                text: qsTr("Yes")
                // Accept the configuration and trigger a rescan
                onClicked: {
                    revertTimer.stop()
                    close()
                    monitorManager.scanMonitors()
                }
            }

            Button {
                text: qsTr("No")
                // Revert the configuration manually
                onClicked: {
                    revertTimer.stop()
                    close()
                    monitorManager.revertMonitorConfiguration()
                }
            }
        }
    }
}

