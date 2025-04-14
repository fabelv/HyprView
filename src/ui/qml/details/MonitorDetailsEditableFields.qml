import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import HyprView

ColumnLayout {

    // Width x Height
    RowLayout {
            Label { text: "Resolution"; Layout.minimumWidth: 100 }
            TextField {
                Layout.fillWidth: true
                enabled: monitorManager?.selectedMonitor_ !== null && monitorManager?.selectedMonitor_ !== undefined
                text: monitorManager?.selectedMonitor_?.width_ ?? 0
                onEditingFinished: {
                    const val = parseFloat(text)
                    if (!isNaN(val) && monitorManager?.selectedMonitor_) monitorManager_.selectedMonitor_.width_ = val
                }
            }
            Label { text: " ; " }
            TextField {
                Layout.fillWidth: true
                enabled: monitorManager?.selectedMonitor_ !== null && monitorManager?.selectedMonitor_ !== undefined
                text: monitorManager?.selectedMonitor_?.height_ ?? 0
                onEditingFinished: {
                    const val = parseFloat(text)
                    if (!isNaN(val) && monitorManager?.selectedMonitor_) monitorManager_.selectedMonitor_.height_ = val
                }
            }
    }

    // Position X and Y
    RowLayout {
        Label { text: "Position (x;y)"; Layout.minimumWidth: 100 }
        TextField {
            Layout.fillWidth: true
            enabled: monitorManager?.selectedMonitor_ !== null && monitorManager?.selectedMonitor_ !== undefined
            text: monitorManager?.selectedMonitor_?.positionX_ ?? 0
            onEditingFinished: {
                const val = parseFloat(text)
                if (!isNaN(val) && monitorManager?.selectedMonitor_) monitorManager.selectedMonitor_.positionX_ = val
            }
        }

        Label { text: " ; " }
        TextField {
            Layout.fillWidth: true
            enabled: monitorManager?.selectedMonitor_ !== null && monitorManager?.selectedMonitor_ !== undefined
            text: monitorManager?.selectedMonitor_?.positionY_ ?? 0
            onEditingFinished: {
                const val = parseFloat(text)
                if (!isNaN(val) && monitorManager?.selectedMonitor_) {
                    monitorManager.selectedMonitor_.positionY_ = val
                }
            }
        }
    }

    // Refresh Rate
    RowLayout {
        Label { text: "Refresh Rate"; Layout.minimumWidth: 100 }
        TextField {
            Layout.fillWidth: true
            enabled: monitorManager?.selectedMonitor_ !== null && monitorManager?.selectedMonitor_ !== undefined

            text: monitorManager?.selectedMonitor_?.refreshRate_ ?? 0
            onEditingFinished: {
                const val = parseFloat(text)
                if (!isNaN(val) && monitorManager?.selectedMonitor_) monitorManager.selectedMonitor_.refreshRate_ = val
            }
        }
    }

    // Scale
    RowLayout {
        Label { text: "Scale"; Layout.minimumWidth: 100 }
        TextField {
            Layout.fillWidth: true
            enabled: monitorManager?.selectedMonitor_ !== null && monitorManager?.selectedMonitor_ !== undefined

            text: monitorManager?.selectedMonitor_?.scale_ ?? 0
            onEditingFinished: {
                const val = parseFloat(text)
                if (!isNaN(val) && monitorManager?.selectedMonitor_) monitorManager.selectedMonitor_.scale_ = val
            }
        }
    }

    // --- Mode Selection ---
    RowLayout {
        Label { text: "Mode:"; Layout.minimumWidth: 100 }

        ComboBox {
            Layout.fillWidth: true
            enabled: monitorManager?.selectedMonitor_ !== null && monitorManager?.selectedMonitor_ !== undefined

            model: monitorManager?.selectedMonitor_ ? monitorHelpers?.getAvailableModes(monitorManager?.selectedMonitor_) : []

            onActivated: {
                if (monitorManager?.selectedMonitor_ && currentIndex >= 0)
                    monitorManager?.selectedMonitor_.applyModeString(model[currentIndex])
            }
        }
    }


    // Transform ComboBox
    RowLayout {
        Label { text: "Transform:"; Layout.minimumWidth: 100 }
        ComboBox {
            Layout.fillWidth: true
            enabled: monitorManager?.selectedMonitor_ !== null && monitorManager?.selectedMonitor_ !== undefined

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

            // Set the initial selection to match the selected monitor's transform
            currentIndex: {
                if (!monitorManager?.selectedMonitor_) return -1;
                for (var i = 0; i < model.length; ++i) {
                    if (model[i].value === monitorManager?.selectedMonitor_.transform_) {
                        return i;
                    }
                }
                return -1;
            }

            onActivated: {
                if (monitorManager?.selectedMonitor_ && currentIndex >= 0) {
                    monitorManager.selectedMonitor_.transform_ = model[index].value
                }
            }
        }
    }

    // Mirror Of
    RowLayout {
        Label { text: "Mirror of:"; Layout.minimumWidth: 100 }

        ComboBox {
            id: mirrorCombo
            Layout.fillWidth: true
            enabled: monitorManager?.selectedMonitor_ !== null && monitorManager?.selectedMonitor_ !== undefined

            model: monitorHelpers?.getAvailableMirrorMonitors(monitorManager?.selectedMonitor_, monitorManager?.monitors_)

            onActivated: {
                monitorManager.selectedMonitor_.mirrorOf_ = model[currentIndex]
            }
        }
    }

    // Checkboxes
    RowLayout {
        Label { text: "Disabled"; Layout.minimumWidth: 100 }
        CheckBox {
            Layout.fillWidth: true
            enabled: monitorManager?.selectedMonitor_ !== null && monitorManager?.selectedMonitor_ !== undefined
            checked: monitorManager?.selectedMonitor_?.disabled_ ?? false
            onToggled: {
                if (monitorManager?.selectedMonitor_)
                    monitorManager.selectedMonitor_.disabled_ = checked
            }
        }
    }

    RowLayout {
        Label { text: "DPMS"; Layout.minimumWidth: 100 }
        CheckBox {
            Layout.fillWidth: true
            enabled: monitorManager?.selectedMonitor_ !== null && monitorManager?.selectedMonitor_ !== undefined
            checked: monitorManager?.selectedMonitor_?.dpmsStatus_ ?? false
            onToggled: {
                if (monitorManager?.selectedMonitor_)
                    monitorManager.selectedMonitor_.dpmsStatus_ = checked
            }
        }
    }
} 
