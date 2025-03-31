import QtQuick.Layouts

import "../components"

ColumnLayout {
    id: mainLayout
    anchors.fill: parent
    spacing: 10

    MonitorScreen {
        Layout.fillWidth: true
        Layout.fillHeight: true
    }

    ButtonBar {}
}
