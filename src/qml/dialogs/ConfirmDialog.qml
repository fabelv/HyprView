import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Dialog {
    id: confirmDialog
    modal: true
    property int countdown: 0

    signal confirmed()
    signal cancelled()

    function start(timeout) {
        countdown = timeout
        title = `Keep this configuration? (${countdown}s)`
        open()
    }

    function updateCountdown(value) {
        countdown = value
        title = `Keep this configuration? (${countdown}s)`
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
                onClicked: confirmDialog.confirmed()
            }
            Button {
                text: "No"
                onClicked: confirmDialog.cancelled()
            }
        }
    }
}
