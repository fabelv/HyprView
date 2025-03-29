import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import "screens"
import "dialogs"
import "components"

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
                confirmDialog.updateCountdown(countdown)
            }
        }
    }

    ConfirmDialog {
        id: confirmDialog
        onConfirmed: {
            revertTimer.stop()
            confirmDialog.close()
        }
        onCancelled: {
            revertTimer.stop()
            confirmDialog.close()
            monitorManager.revertAplly()
        }
    }

    function showConfirmDialog() {
        countdown = confirmTimeout
        confirmDialog.start(countdown)
        revertTimer.start()
    }

    menuBar: AppMenuBar { }

    ColumnLayout {
        anchors.fill: parent
        spacing: 10

        MonitorScreen {
            Layout.fillWidth: true
            Layout.fillHeight: true
        }

        ButtonBar {
            onApplyClicked: {
                monitorManager.apply()
                window.showConfirmDialog()
            }
            onRescanClicked: monitorManager.rescan()
        }
    }
}

