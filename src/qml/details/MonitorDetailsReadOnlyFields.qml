import QtQuick.Controls
import QtQuick.Layouts

ColumnLayout {
    id: readOnlyFields
    property var selectedMonitor

    RowLayout {
        Label { text: "ID:"; Layout.minimumWidth: 100 }
        Label { text: readOnlyFields.selectedMonitor?.id }
    }

    RowLayout {
        Label { text: "Name:"; Layout.minimumWidth: 100 }
        Label { text: readOnlyFields.selectedMonitor?.name }
    }

    RowLayout {
        Label { text: "Description:"; Layout.minimumWidth: 100 }
        Label { text: readOnlyFields.selectedMonitor?.description }
    }

    RowLayout {
        Label { text: "Make:"; Layout.minimumWidth: 100 }
        Label { text: readOnlyFields.selectedMonitor?.make }
    }

    RowLayout {
        Label { text: "Model:"; Layout.minimumWidth: 100 }
        Label { text: readOnlyFields.selectedMonitor?.model }
    }

    RowLayout {
        Label { text: "Serial:"; Layout.minimumWidth: 100 }
        Label { text: readOnlyFields.selectedMonitor?.serial }
    }

    RowLayout {
        Label { text: "VRR:"; Layout.minimumWidth: 100 }
        Label { text:  readOnlyFields.selectedMonitor?.vrr }
    }

    RowLayout {
        Label { text: "Solitary:"; Layout.minimumWidth: 100 }
        Label { text: readOnlyFields.selectedMonitor?.solitary }
    }

    RowLayout {
        Label { text: "Tearing:"; Layout.minimumWidth: 100 }
        Label { text: readOnlyFields.selectedMonitor?.activelyTearing }
    }

    RowLayout {
        Label { text: "Scanout To:"; Layout.minimumWidth: 100 }
        Label { text: readOnlyFields.selectedMonitor?.directScanoutTo }
    }

    RowLayout {
        Label { text: "Current Format:"; Layout.minimumWidth: 100 }
        Label { text: readOnlyFields.selectedMonitor?.currentFormat }
    }
}
