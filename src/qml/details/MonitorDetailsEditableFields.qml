import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import HyprView

ColumnLayout {
    id: editableFields
    spacing: 6

    property var selectedMonitor
    property var mirrorCandidates

    // Width x Height
    RowLayout {
            Label { text: "Resolution"; Layout.minimumWidth: 100 }
            TextField {
                Layout.fillWidth: true
                enabled: !!editableFields.selectedMonitor
                text: editableFields.selectedMonitor?.width ?? 0
                onEditingFinished: {
                    const val = parseFloat(text)
                    if (!isNaN(val) && editableFields.selectedMonitor) editableFields.selectedMonitor.width = val
                }
            }
            Label { text: " ; " }
            TextField {
                Layout.fillWidth: true
                enabled: !!editableFields.selectedMonitor
                text: editableFields.selectedMonitor?.height ?? 0
                onEditingFinished: {
                    const val = parseFloat(text)
                    if (!isNaN(val) && editableFields.selectedMonitor) editableFields.selectedMonitor.height = val
                }
            }
    }


    // Position X and Y
    RowLayout {
        Label { text: "Position (x;y)"; Layout.minimumWidth: 100 }
        TextField {
            Layout.fillWidth: true
            enabled: !!editableFields.selectedMonitor
            text: editableFields.selectedMonitor?.positionX ?? 0
            onEditingFinished: {
                const val = parseFloat(text)
                if (!isNaN(val) && editableFields.selectedMonitor) editableFields.selectedMonitor.positionX = val
            }
        }

        Label { text: " ; " }
        TextField {
            Layout.fillWidth: true
            enabled: !!editableFields.selectedMonitor
            text: editableFields.selectedMonitor?.positionY ?? 0
            onEditingFinished: {
                const val = parseFloat(text)
                if (!isNaN(val) && editableFields.selectedMonitor) editableFields.selectedMonitor.positionY = val
            }
        }
    }

    // Refresh Rate
    RowLayout {
        Label { text: "Refresh Rate"; Layout.minimumWidth: 100 }
        TextField {
            Layout.fillWidth: true
            enabled: !!editableFields.selectedMonitor
            text: editableFields.selectedMonitor?.refreshRate ?? 0
            onEditingFinished: {
                const val = parseFloat(text)
                if (!isNaN(val) && editableFields.selectedMonitor) editableFields.selectedMonitor.refreshRate = val
            }
        }
    }

    // --- Mode Selection ---
    RowLayout {
        Label { text: "Mode:"; Layout.minimumWidth: 100 }
        ComboBox {
            Layout.fillWidth: true
            model: editableFields.selectedMonitor ? editableFields.selectedMonitor.availableModes : []
            Component.onCompleted: {
                if (editableFields.selectedMonitor)
                    currentIndex = model.indexOf(editableFields.selectedMonitor.generateCurrentMode())
            }
            onCurrentIndexChanged: {
                if (editableFields.selectedMonitor && currentIndex >= 0)
                    editableFields.selectedMonitor.applyModeString(model[currentIndex])
            }
        }
    }

    // Transform ComboBox
    RowLayout {
        Label { text: "Transform:"; Layout.minimumWidth: 100 }
        ComboBox {
            Layout.fillWidth: true
            model: [
                { text: "Normal", value: Transform.Normal },
                { text: "90°", value: Transform.Rotate90 },
                { text: "180°", value: Transform.Rotate180 },
                { text: "270°", value: Transform.Rotate270 },
                { text: "Flipped", value: Transform.Flipped },
                { text: "Flipped + 90°", value: Transform.FlippedRotate90 },
                { text: "Flipped + 180°", value: Transform.FlippedRotate180 },
                { text: "Flipped + 270°", value: Transform.FlippedRotate270 }
            ]
            textRole: "text"
            Component.onCompleted: {
                if (editableFields.selectedMonitor)
                    currentIndex = model.findIndex(v => v.value === selectedMonitor.transform)
            }
            onCurrentIndexChanged: {
                if (editableFields.selectedMonitor && model[currentIndex])
                    editableFields.selectedMonitor.transform = model[currentIndex].value
            }
        }
    }

    // Mirror Of
    RowLayout {
        Label { text: "Mirror of:"; Layout.minimumWidth: 100 }
        ComboBox {
            Layout.fillWidth: true
            model: editableFields.mirrorCandidates
            textRole: "name"
            Component.onCompleted: {
                if (editableFields.selectedMonitor) {
                    const index = editableFields.mirrorCandidates.findIndex(m => m.name === selectedMonitor.mirrorOf)
                    currentIndex = index >= 0 ? index : 0
                }
            }
            onCurrentIndexChanged: {
                if (editableFields.selectedMonitor) {
                    const value = editableFields.mirrorCandidates[currentIndex].name
                    editableFields.selectedMonitor.mirrorOf = value === "None" ? null : value
                }
            }
        }
    }

    // Checkboxes
    RowLayout {
        Label { text: "Disabled"; Layout.minimumWidth: 100 }
        CheckBox {
            Layout.fillWidth: true
            enabled: !!editableFields.selectedMonitor
            checked: editableFields.selectedMonitor?.disabled ?? false
            onToggled: {
                if (editableFields.selectedMonitor)
                    editableFields.selectedMonitor.disabled = checked
            }
        }
    }

    RowLayout {
        Label { text: "DPMS"; Layout.minimumWidth: 100 }
        CheckBox {
            Layout.fillWidth: true
            enabled: !!editableFields.selectedMonitor
            checked: editableFields.selectedMonitor?.dpmsStatus ?? false
            onToggled: {
                if (editableFields.selectedMonitor)
                    editableFields.selectedMonitor.dpmsStatus = checked
            }
        }
    }
} 
