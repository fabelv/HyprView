import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import HyprView 1.0

ScrollView {
    id: scrollView

    ColumnLayout {
        id: root

        Label {
            text: "Monitor Details"
            font.pixelSize: 20
            Layout.alignment: Qt.AlignHCenter
        }

        MonitorDetailsReadOnlyFields {}

        MonitorDetailsEditableFields {}
    }
}
