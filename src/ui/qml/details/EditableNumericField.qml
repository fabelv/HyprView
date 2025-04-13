import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

RowLayout {
    property alias label: label.text
    property real value1: 0
    property real value2: 0
    signal value1Edited(string val)
    signal value2Edited(string val)

    Label { id: label; Layout.minimumWidth: 100 }
    TextField {
        Layout.fillWidth: true
        text: value1
        onEditingFinished: value1Edited(text)
    }
    Label { text: ";" }
    TextField {
        Layout.fillWidth: true
        text: value2
        onEditingFinished: value2Edited(text)
    }
}
