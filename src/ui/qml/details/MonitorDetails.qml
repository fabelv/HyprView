import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import HyprView 1.0

ScrollView {
    id: scrollView

    ColumnLayout {
        id: root

        Item { height: 12 }

        MonitorDetailsReadOnlyFields {}

        MonitorDetailsEditableFields {}
    }
}
