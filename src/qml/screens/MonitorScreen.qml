import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import "../details"
import "../preview"

RowLayout {
    Layout.fillWidth: true
    Layout.fillHeight: true
    spacing: 10

    MonitorPreview {
        Layout.preferredWidth: 0.6 * parent.width
        Layout.fillHeight: true
    }

    MonitorDetails {
        Layout.fillWidth: true
        Layout.fillHeight: true
    }
}
