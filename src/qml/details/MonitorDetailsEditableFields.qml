import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import HyprView

ColumnLayout {
    visible: monitorManager.selectedMonitor !== null
    property var mirrorCandidates

    // Width x Height
    RowLayout {
            Label { text: "Resolution"; Layout.minimumWidth: 100 }
            TextField {
                Layout.fillWidth: true
                enabled: !!monitorManager.selectedMonitor
                text: monitorManager.selectedMonitor?.width ?? 0
                onEditingFinished: {
                    const val = parseFloat(text)
                    if (!isNaN(val) && monitorManager.selectedMonitor) monitorManager.selectedMonitor.width = val
                }
            }
            Label { text: " ; " }
            TextField {
                Layout.fillWidth: true
                enabled: !!monitorManager.selectedMonitor
                text: monitorManager.selectedMonitor?.height ?? 0
                onEditingFinished: {
                    const val = parseFloat(text)
                    if (!isNaN(val) && monitorManager.selectedMonitor) monitorManager.selectedMonitor.height = val
                }
            }
    }


    // Position X and Y
    RowLayout {
        Label { text: "Position (x;y)"; Layout.minimumWidth: 100 }
        TextField {
            Layout.fillWidth: true
            enabled: !!monitorManager.selectedMonitor
            text: monitorManager.selectedMonitor?.positionX ?? 0
            onEditingFinished: {
                const val = parseFloat(text)
                if (!isNaN(val) && monitorManager.selectedMonitor) monitorManager.selectedMonitor.positionX = val
            }
        }

        Label { text: " ; " }
        TextField {
            Layout.fillWidth: true
            enabled: !!monitorManager.selectedMonitor
            text: monitorManager.selectedMonitor?.positionY ?? 0
            onEditingFinished: {
                const val = parseFloat(text)
                if (!isNaN(val) && monitorManager.selectedMonitor) monitorManager.selectedMonitor.positionY = val
            }
        }
    }

    // Refresh Rate
    RowLayout {
        Label { text: "Refresh Rate"; Layout.minimumWidth: 100 }
        TextField {
            Layout.fillWidth: true
            enabled: !!monitorManager.selectedMonitor
            text: monitorManager.selectedMonitor?.refreshRate ?? 0
            onEditingFinished: {
                const val = parseFloat(text)
                if (!isNaN(val) && monitorManager.selectedMonitor) monitorManager.selectedMonitor.refreshRate = val
            }
        }
    }

    // Scale
    RowLayout {
        Label { text: "Scale"; Layout.minimumWidth: 100 }
        TextField {
            Layout.fillWidth: true
            enabled: !!monitorManager.selectedMonitor
            text: monitorManager.selectedMonitor?.scale ?? 0
            onEditingFinished: {
                const val = parseFloat(text)
                if (!isNaN(val) && monitorManager.selectedMonitor) monitorManager.selectedMonitor.scale = val
            }
        }
    }


    // --- Mode Selection ---
    RowLayout {
        Label { text: "Mode:"; Layout.minimumWidth: 100 }
        ComboBox {
            Layout.fillWidth: true
            model: monitorManager.selectedMonitor ? monitorManager.selectedMonitor.availableModes : []
            Component.onCompleted: {
                if (monitorManager.selectedMonitor)
                    currentIndex = model.indexOf(monitorManager.selectedMonitor.generateCurrentMode())
            }
            onCurrentIndexChanged: {
                if (monitorManager.selectedMonitor && currentIndex >= 0)
                    monitorManager.selectedMonitor.applyModeString(model[currentIndex])
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
                if (monitorManager.selectedMonitor)
                    currentIndex = model.findIndex(v => v.value === monitorManager.selectedMonitor.transform)
            }
            onCurrentIndexChanged: {
                if (monitorManager.selectedMonitor && model[currentIndex])
                    monitorManager.selectedMonitor.transform = model[currentIndex].value
            }
        }
    }

    // Mirror Of
    RowLayout {
        Label { text: "Mirror of:"; Layout.minimumWidth: 100 }
        ComboBox {
            Layout.fillWidth: true
            model: monitorManager.mirrorCandidates
            textRole: "name"
            Component.onCompleted: {
                if (monitorManager.selectedMonitor) {
                    const index = monitorManager.mirrorCandidates.findIndex(m => m.name === monitorManager.selectedMonitor.mirrorOf)
                    currentIndex = index >= 0 ? index : 0
                }
            }
            onCurrentIndexChanged: {
                if (monitorManager.selectedMonitor) {
                    const value = monitorManager.mirrorCandidates[currentIndex].name
                    monitorManager.selectedMonitor.mirrorOf = value === "None" ? null : value
                }
            }
        }
    }

    // Checkboxes
    RowLayout {
        Label { text: "Disabled"; Layout.minimumWidth: 100 }
        CheckBox {
            Layout.fillWidth: true
            enabled: !!monitorManager.selectedMonitor
            checked: monitorManager.selectedMonitor?.disabled ?? false
            onToggled: {
                if (monitorManager.selectedMonitor)
                    monitorManager.selectedMonitor.disabled = checked
            }
        }
    }

    RowLayout {
        Label { text: "DPMS"; Layout.minimumWidth: 100 }
        CheckBox {
            Layout.fillWidth: true
            enabled: !!monitorManager.selectedMonitor
            checked: monitorManager.selectedMonitor?.dpmsStatus ?? false
            onToggled: {
                if (monitorManager.selectedMonitor)
                    monitorManager.selectedMonitor.dpmsStatus = checked
            }
        }
    }
} 
