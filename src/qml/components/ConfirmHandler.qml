import QtQuick

import "../dialogs"

Item {
    id: confirmHandler

    property alias dialogVisible: confirmDialog.visible
    property int timeout: 15
    property int countdown: timeout

    signal confirmed()
    signal cancelled()

    Timer {
        id: revertTimer
        interval: 1000
        running: false
        repeat: true
        onTriggered: {
            confirmHandler.countdown--
            if (confirmHandler.countdown <= 0) {
                revertTimer.stop()
                confirmDialog.close()
                confirmHandler.cancelled()
            } else {
                confirmDialog.updateCountdown(confirmHandler.countdown)
            }
        }
    }

    ConfirmDialog {
        id: confirmDialog
        onConfirmed: {
            revertTimer.stop()
            confirmDialog.close()
            confirmHandler.confirmed()
        }
        onCancelled: {
            revertTimer.stop()
            confirmDialog.close()
            confirmHandler.cancelled()
        }
    }

    function show() {
        confirmHandler.countdown = confirmHandler.timeout
        confirmDialog.start(confirmHandler.countdown)
        revertTimer.start()
    }
}
