import QtQuick.Layouts

import "../components"

ColumnLayout {
    id: mainLayout
    anchors.fill: parent

    MonitorScreen {
        Layout.fillWidth: true
        Layout.fillHeight: true
    }

    ButtonBar {}
}
