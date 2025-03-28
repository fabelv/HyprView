import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

RowLayout {
    id: root

    property bool checked: false
    property alias label: label.text
    property alias enabled: checkbox.enabled
    signal toggled(bool checked)

    spacing: 10

    Label {
        id: label
        Layout.minimumWidth: 100
    }

    CheckBox {
        id: checkbox
        Layout.fillWidth: true
        checked: root.checked
        onToggled: {
            root.checked = checked
            root.toggled(checked)
        }
    }
}

