import QtQuick.Controls
import QtQuick.Layouts

ColumnLayout {
    visible: monitorManager.getSelectedMonitor() != null

    RowLayout {
        Label { text: "ID:"; Layout.minimumWidth: 100 }
        Label { text: monitorManager.getSelectedMonitor()?.id_ ?? "" }
    }

    RowLayout {
        Label { text: "Name:"; Layout.minimumWidth: 100 }
        Label { text: monitorManager.getSelectedMonitor()?.name_ }
    }

    RowLayout {
        Label { text: "Description:"; Layout.minimumWidth: 100 }
        Label { text: monitorManager.getSelectedMonitor()?.description_ }
    }

    RowLayout {
        Label { text: "Make:"; Layout.minimumWidth: 100 }
        Label { text: monitorManager.getSelectedMonitor()?.make_ }
    }

    RowLayout {
        Label { text: "Model:"; Layout.minimumWidth: 100 }
        Label { text: monitorManager.getSelectedMonitor()?.model_ }
    }

    RowLayout {
        Label { text: "Serial:"; Layout.minimumWidth: 100 }
        Label { text: monitorManager.getSelectedMonitor()?.serial_ }
    }

    RowLayout {
        Label { text: "VRR:"; Layout.minimumWidth: 100 }
        Label { text:  monitorManager.getSelectedMonitor()?.vrr_ }
    }

    RowLayout {
        Label { text: "Solitary:"; Layout.minimumWidth: 100 }
        Label { text: monitorManager.getSelectedMonitor()?.solitary_ }
    }

    RowLayout {
        Label { text: "Tearing:"; Layout.minimumWidth: 100 }
        Label { text: monitorManager.getSelectedMonitor()?.activelyTearing_ }
    }

    RowLayout {
        Label { text: "Scanout To:"; Layout.minimumWidth: 100 }
        Label { text: monitorManager.getSelectedMonitor()?.directScanoutTo_ }
    }

    RowLayout {
        Label { text: "Current Format:"; Layout.minimumWidth: 100 }
        Label { text: monitorManager.getSelectedMonitor()?.currentFormat_ }
    }
}

