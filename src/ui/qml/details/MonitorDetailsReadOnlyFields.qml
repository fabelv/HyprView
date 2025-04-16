import QtQuick.Controls
import QtQuick.Layouts

ColumnLayout {

    RowLayout {
        Label { text: "ID:"; Layout.minimumWidth: 100 }
        Label { text: monitorManager?.selectedMonitor_?.id_ ?? "" }
    }

    RowLayout {
        Label { text: "Name:"; Layout.minimumWidth: 100 }
        Label { text: monitorManager?.selectedMonitor_?.name_ ?? "" }
    }

    RowLayout {
        Label { text: "Description:"; Layout.minimumWidth: 100 }
        Label { text: monitorManager?.selectedMonitor_?.description_ ?? "" }
    }

    RowLayout {
        Label { text: "Make:"; Layout.minimumWidth: 100 }
        Label { text: monitorManager?.selectedMonitor_?.make_ ?? "" }
    }

    RowLayout {
        Label { text: "Model:"; Layout.minimumWidth: 100 }
        Label { text: monitorManager?.selectedMonitor_?.model_ ?? "" }
    }

    RowLayout {
        Label { text: "Serial:"; Layout.minimumWidth: 100 }
        Label { text: monitorManager?.selectedMonitor_?.serial_ ?? "" }
    }

    RowLayout {
        Label { text: "VRR:"; Layout.minimumWidth: 100 }
        Label { text:  monitorManager?.selectedMonitor_?.vrr_ ?? "" }
    }

    RowLayout {
        Label { text: "Solitary:"; Layout.minimumWidth: 100 }
        Label { text: monitorManager?.selectedMonitor_?.solitary_ ?? "" }
    }

    RowLayout {
        Label { text: "Tearing:"; Layout.minimumWidth: 100 }
        Label { text: monitorManager?.selectedMonitor_?.activelyTearing_ ?? "" }
    }

    RowLayout {
        Label { text: "Scanout To:"; Layout.minimumWidth: 100 }
        Label { text: monitorManager?.selectedMonitor_?.directScanoutTo_ ?? "" }
    }

    RowLayout {
        Label { text: "Current Format:"; Layout.minimumWidth: 100 }
        Label { text: monitorManager?.selectedMonitor_?.currentFormat_ ?? "" }
    }
}

