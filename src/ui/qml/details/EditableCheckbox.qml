import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

RowLayout {
    property alias label: label.text
    property bool checked: false
    signal toggled(bool val)

    Label { id: label; Layout.minimumWidth: 100 }
    CheckBox {
        Layout.fillWidth: true
        checked: parent.checked
        onToggled: toggled(checked)
    }
}
