import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import HyprView

ColumnLayout {
    property var monitor: monitorManager.getSelectedMonitor()

    function updateIfValid(field, value) {
        const val = parseFloat(value)
        if (!isNaN(val) && monitor) monitor[field] = val
    }

    function setIfMonitor(field, value) {
        if (monitor) monitor[field] = value
    }

    EditableNumericField {
        label: "Resolution"
        value1: monitor?.width_ ?? 0
        value2: monitor?.height_ ?? 0
        onValue1Edited: v => updateIfValid("width_", v)
        onValue2Edited: v => updateIfValid("height_", v)
    }

    EditableNumericField {
        label: "Position (x;y)"
        value1: monitor?.positionX_ ?? 0
        value2: monitor?.positionY_ ?? 0
        onValue1Edited: v => updateIfValid("positionX_", v)
        onValue2Edited: v => updateIfValid("positionY_", v)
    }

    EditableSingleField {
        label: "Refresh Rate"
        value: monitor?.refreshRate_ ?? 0
        onEdited: v => updateIfValid("refreshRate_", v)
    }

    EditableSingleField {
        label: "Scale"
        value: monitor?.scale_ ?? 0
        onEdited: v => updateIfValid("scale_", v)
    }

    // Mode ComboBox
    RowLayout {
        Label { text: "Mode:"; Layout.minimumWidth: 100 }
        ComboBox {
            Layout.fillWidth: true
            model: monitor?.availableModes_ ?? []
            Component.onCompleted: {
                if (monitor) currentIndex = model.indexOf(monitor.generateCurrentMode())
            }
            onCurrentIndexChanged: {
                if (monitor && currentIndex >= 0)
                    monitor.applyModeString(model[currentIndex])
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
                if (monitor)
                    currentIndex = model.findIndex(v => v.value === monitor.transform_)
            }
            onCurrentIndexChanged: {
                if (monitor && model[currentIndex])
                    monitor.transform_ = model[currentIndex].value
            }
        }
    }

    // Mirror Of
    RowLayout {
        Label { text: "Mirror of:"; Layout.minimumWidth: 100 }
        ComboBox {
            Layout.fillWidth: true
            model: monitorHelpers.getAvailableMirrorMonitors(monitor, monitorManager.monitors_)
        }
    }

    EditableCheckbox {
        label: "Disabled"
        checked: monitor?.disabled_ ?? false
        onToggled: c => setIfMonitor("disabled_", c)
    }

    EditableCheckbox {
        label: "DPMS"
        checked: monitor?.dpmsStatus_ ?? false
        onToggled: c => setIfMonitor("dpmsStatus_", c)
    }
}

