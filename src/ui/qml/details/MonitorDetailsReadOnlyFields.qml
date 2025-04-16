import QtQuick.Controls
import QtQuick.Layouts

ColumnLayout {
    Layout.fillWidth: true
    spacing: 8

    RowLayout {
        Layout.fillWidth: true
        Label { text: "ID:"; Layout.minimumWidth: 100 }
        Label {
            text: monitorManager?.selectedMonitor_?.id_ ?? ""
            Layout.fillWidth: true
        }
    }

    RowLayout {
        Layout.fillWidth: true
        Label { text: "Name:"; Layout.minimumWidth: 100 }
        Label {
            text: monitorManager?.selectedMonitor_?.name_ ?? ""
            Layout.fillWidth: true
        }
    }

    RowLayout {
        Layout.fillWidth: true
        Label { text: "Description:"; Layout.minimumWidth: 100 }
        Label {
            text: monitorManager?.selectedMonitor_?.description_ ?? ""
            Layout.fillWidth: true
            Layout.maximumWidth: 200
        }
    }

    RowLayout {
        Layout.fillWidth: true
        Label { text: "Make:"; Layout.minimumWidth: 100 }
        Label {
            text: monitorManager?.selectedMonitor_?.make_ ?? ""
            Layout.fillWidth: true
        }
    }

    RowLayout {
        Layout.fillWidth: true
        Label { text: "Model:"; Layout.minimumWidth: 100 }
        Label {
            text: monitorManager?.selectedMonitor_?.model_ ?? ""
            Layout.fillWidth: true
        }
    }

    RowLayout {
        Layout.fillWidth: true
        Label { text: "Serial:"; Layout.minimumWidth: 100 }
        Label {
            text: monitorManager?.selectedMonitor_?.serial_ ?? ""
            Layout.fillWidth: true
        }
    }

    RowLayout {
        Layout.fillWidth: true
        Label { text: "VRR:"; Layout.minimumWidth: 100 }
        Label {
            text: monitorManager?.selectedMonitor_?.vrr_ ?? ""
            Layout.fillWidth: true
        }
    }

    RowLayout {
        Layout.fillWidth: true
        Label { text: "Solitary:"; Layout.minimumWidth: 100 }
        Label {
            text: monitorManager?.selectedMonitor_?.solitary_ ?? ""
            Layout.fillWidth: true
        }
    }

    RowLayout {
        Layout.fillWidth: true
        Label { text: "Tearing:"; Layout.minimumWidth: 100 }
        Label {
            text: monitorManager?.selectedMonitor_?.activelyTearing_ ?? ""
            Layout.fillWidth: true
        }
    }

    RowLayout {
        Layout.fillWidth: true
        Label { text: "Scanout To:"; Layout.minimumWidth: 100 }
        Label {
            text: monitorManager?.selectedMonitor_?.directScanoutTo_ ?? ""
            Layout.fillWidth: true
        }
    }

    RowLayout {
        Layout.fillWidth: true
        Label { text: "Current Format:"; Layout.minimumWidth: 100 }
        Label {
            text: monitorManager?.selectedMonitor_?.currentFormat_ ?? ""
            Layout.fillWidth: true
        }
    }
}
