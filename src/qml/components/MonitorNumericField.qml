import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

RowLayout {
    id: root

    property alias label: label.text
    property bool editable: true
    property real fieldValue: 0
    signal valueChanged(real newValue)

    spacing: 10

    Label {
        id: label
        Layout.minimumWidth: 100
    }

    TextField {
        id: input
        Layout.fillWidth: true
        enabled: editable
        inputMethodHints: Qt.ImhFormattedNumbersOnly

        text: fieldValue.toString()

        onEditingFinished: {
            const num = parseFloat(text)
            if (!isNaN(num) && num !== fieldValue) {
                fieldValue = num
                valueChanged(num)
            }
        }
    }
}

