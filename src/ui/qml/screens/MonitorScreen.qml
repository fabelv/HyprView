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
        width: parent.width * 0.6
    }

    MonitorDetails {
        anchors.left: preview.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.right: parent.right
    }
}

