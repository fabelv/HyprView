import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import HyprView 1.0

ScrollView {
    id: scrollView
    ScrollBar.vertical.policy: ScrollBar.AsNeeded

    property var selectedMonitor
    property var monitors
    property var mirrorCandidates: []

    function updateMirrorCandidates() {
        if (!selectedMonitor || !monitors) return

        mirrorCandidates = [{ name: "None" }]
        for (let i = 0; i < monitors.length; ++i) {
            if (monitors[i].name !== selectedMonitor.name) {
                mirrorCandidates.push(monitors[i])
            }
        }
    }

    Component.onCompleted: updateMirrorCandidates()

    ColumnLayout {
        id: root
        spacing: 6

        Label {
            text: "Monitor Details"
            font.pixelSize: 20
            Layout.alignment: Qt.AlignHCenter
        }

        MonitorDetailsReadOnlyFields {
            selectedMonitor: scrollView.selectedMonitor
        }

        MonitorDetailsEditableFields {
            selectedMonitor: scrollView.selectedMonitor
            mirrorCandidates : scrollView.mirrorCandidates
        }
    }
}
