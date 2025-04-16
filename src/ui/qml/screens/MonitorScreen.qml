import QtQuick

import "../details"
import "../preview"


Item {
    id: root

    MonitorPreview {
        id: preview
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.right: details.left  // ⬅️ link to details

        // Optional: avoid overlap or ensure no 0-width issue
        anchors.rightMargin: 0
    }

    MonitorDetails {
        id: details
        width: 400  // ⬅️ fixed width
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.right: parent.right
    }
}

