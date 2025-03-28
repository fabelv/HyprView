import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

RowLayout {
    id: buttonBar
    spacing: 10
    Layout.alignment: Qt.AlignHCenter

    signal applyClicked()
    signal rescanClicked()

    Button {
        text: "Apply"
        onClicked: buttonBar.applyClicked()
    }

    Button {
        text: "Rescan"
        onClicked: buttonBar.rescanClicked()
    }
}
