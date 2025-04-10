import QtQuick.Controls
import QtQuick.Layouts

ColumnLayout {
    visible: monitorManager.selectedMonitor !== null

    RowLayout {
        Label { text: "ID:"; Layout.minimumWidth: 100 }
        Label { text: monitorManager.selectedMonitor?.id ?? "" }
    }

    RowLayout {
        Label { text: "Name:"; Layout.minimumWidth: 100 }
        Label { text: monitorManager.selectedMonitor?.name }
    }

    RowLayout {
        Label { text: "Description:"; Layout.minimumWidth: 100 }
        Label { text: monitorManager.selectedMonitor?.description }
    }

    RowLayout {
        Label { text: "Make:"; Layout.minimumWidth: 100 }
        Label { text: monitorManager.selectedMonitor?.make }
    }

    RowLayout {
        Label { text: "Model:"; Layout.minimumWidth: 100 }
        Label { text: monitorManager.selectedMonitor?.model }
    }

    RowLayout {
        Label { text: "Serial:"; Layout.minimumWidth: 100 }
        Label { text: monitorManager.selectedMonitor?.serial }
    }

    RowLayout {
        Label { text: "VRR:"; Layout.minimumWidth: 100 }
        Label { text:  monitorManager.selectedMonitor?.vrr }
    }

    RowLayout {
        Label { text: "Solitary:"; Layout.minimumWidth: 100 }
        Label { text: monitorManager.selectedMonitor?.solitary }
    }

    RowLayout {
        Label { text: "Tearing:"; Layout.minimumWidth: 100 }
        Label { text: monitorManager.selectedMonitor?.activelyTearing }
    }

    RowLayout {
        Label { text: "Scanout To:"; Layout.minimumWidth: 100 }
        Label { text: monitorManager.selectedMonitor?.directScanoutTo }
    }

    RowLayout {
        Label { text: "Current Format:"; Layout.minimumWidth: 100 }
        Label { text: monitorManager.selectedMonitor?.currentFormat }
    }
}
