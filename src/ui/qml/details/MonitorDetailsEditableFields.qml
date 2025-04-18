import Core 1.0
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
                    if (!isNaN(val) && monitorManager?.selectedMonitor_) {
                        monitorManager.selectedMonitor_.width_ = val
                        monitorManager.selectedMonitor_.positionUpdatedByDetailsField()
                    }
                }
            }
            Label { text: " ; " }
            TextField {
                Layout.fillWidth: true
                enabled: monitorManager?.selectedMonitor_ !== null && monitorManager?.selectedMonitor_ !== undefined
                text: monitorManager?.selectedMonitor_?.height_ ?? 0
                onEditingFinished: {
                    const val = parseFloat(text)
                    if (!isNaN(val) && monitorManager?.selectedMonitor_) {
                        monitorManager.selectedMonitor_.height_ = val
                        monitorManager.selectedMonitor_.positionUpdatedByDetailsField()
                    }
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
                if (!isNaN(val) && monitorManager?.selectedMonitor_) {
                    monitorManager.selectedMonitor_.positionX_ = val
                
                        monitorManager.selectedMonitor_.positionUpdatedByDetailsField()
                }
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

                        monitorManager.selectedMonitor_.positionUpdatedByDetailsField()
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
                if (!isNaN(val) && monitorManager?.selectedMonitor_) {
                    monitorManager.selectedMonitor_.refreshRate_ = val
                    monitorManager.selectedMonitor_.positionUpdatedByDetailsField()
                }
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
                if (!isNaN(val) && monitorManager?.selectedMonitor_) {
                    monitorManager.selectedMonitor_.scale_ = val

                        monitorManager.selectedMonitor_.positionUpdatedByDetailsField()
                }
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
                        monitorManager.selectedMonitor_.positionUpdatedByDetailsField()
            }
        }
    }


    // Transform ComboBox
    RowLayout {
        Label { text: "Transform:"; Layout.minimumWidth: 100 }
        ComboBox {
            Layout.fillWidth: true
            enabled: monitorManager?.selectedMonitor_ !== null && monitorManager?.selectedMonitor_ !== undefined

            model: TransformHelper.transformModel()
            textRole: "text"

            onActivated: {
                if (monitorManager?.selectedMonitor_ && currentIndex >= 0) {
                    monitorManager.selectedMonitor_.transform_ = model[index].value
                        monitorManager.selectedMonitor_.positionUpdatedByDetailsField()
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
                        monitorManager.selectedMonitor_.positionUpdatedByDetailsField()
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
                        monitorManager.selectedMonitor_.positionUpdatedByDetailsField()
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
                        monitorManager.selectedMonitor_.positionUpdatedByDetailsField()
            }
        }
    }
} 
