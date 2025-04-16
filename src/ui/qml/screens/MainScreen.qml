import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import "../components"

ColumnLayout {
    id: mainLayout
    anchors.fill: parent
    objectName: "mainScreen"

    MonitorScreen {
        Layout.fillWidth: true
        Layout.fillHeight: true
        // Takes up all available space above the button bar
    }

    ButtonBar {
        // If needed, you can also give this fixed height or layout hints
        Layout.fillWidth: true
    }
}

