import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

RowLayout {
    property alias label: label.text
    property real value: 0
    signal edited(string val)

    Label { id: label; Layout.minimumWidth: 100 }
    TextField {
        Layout.fillWidth: true
        text: value
        onEditingFinished: edited(text)
    }
}
