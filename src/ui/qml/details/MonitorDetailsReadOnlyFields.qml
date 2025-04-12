import QtQuick.Controls
import QtQuick.Layouts

ColumnLayout {
    visible: monitorManager.selectedMonitorIndex_ >= 0

    RowLayout {
        Label { text: "ID:"; Layout.minimumWidth: 100 }
        Label { text: monitorManager.monitors_[selectedMonitorIndex_]?.id ?? "" }
    }

    RowLayout {
        Label { text: "Name:"; Layout.minimumWidth: 100 }
        Label { text: monitorManager.monitors_[selectedMonitorIndex_]?.name }
    }

    RowLayout {
        Label { text: "Description:"; Layout.minimumWidth: 100 }
        Label { text: monitorManager.monitors_[selectedMonitorIndex_]?.description }
    }

    RowLayout {
        Label { text: "Make:"; Layout.minimumWidth: 100 }
        Label { text: monitorManager.monitors_[selectedMonitorIndex_]?.make }
    }

    RowLayout {
        Label { text: "Model:"; Layout.minimumWidth: 100 }
        Label { text: monitorManager.monitors_[selectedMonitorIndex_]?.model }
    }

    RowLayout {
        Label { text: "Serial:"; Layout.minimumWidth: 100 }
        Label { text: monitorManager.monitors_[selectedMonitorIndex_]?.serial }
    }

    RowLayout {
        Label { text: "VRR:"; Layout.minimumWidth: 100 }
        Label { text:  monitorManager.monitors_[selectedMonitorIndex_]?.vrr }
    }

    RowLayout {
        Label { text: "Solitary:"; Layout.minimumWidth: 100 }
        Label { text: monitorManager.monitors_[selectedMonitorIndex_]?.solitary }
    }

    RowLayout {
        Label { text: "Tearing:"; Layout.minimumWidth: 100 }
        Label { text: monitorManager.monitors_[selectedMonitorIndex_]?.activelyTearing }
    }

    RowLayout {
        Label { text: "Scanout To:"; Layout.minimumWidth: 100 }
        Label { text: monitorManager.monitors_[selectedMonitorIndex_]?.directScanoutTo }
    }

    RowLayout {
        Label { text: "Current Format:"; Layout.minimumWidth: 100 }
        Label { text: monitorManager.monitors_[selectedMonitorIndex_]?.currentFormat }
    }
}
