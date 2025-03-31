import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import HyprView 1.0

ScrollView {
    id: scrollView
    ScrollBar.vertical.policy: ScrollBar.AsNeeded

    property var mirrorCandidates: []

    function updateMirrorCandidates() {
        if (!monitorManager.selectedMonitor || !monitorManager.monitors) return

        mirrorCandidates = [{ name: "None" }]
        for (let i = 0; i < monitorManager.monitors.length; ++i) {
            if (monitorManager.monitors[i].name !== monitorManager.selectedMonitor.name) {
                mirrorCandidates.push(monitorManager.monitors[i])
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
        }

        MonitorDetailsEditableFields {
            mirrorCandidates : scrollView.mirrorCandidates
        }
    }
}
