import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import HyprView 1.0


ScrollView {
    id: scrollView
    ScrollBar.vertical.policy: ScrollBar.AsNeeded

    property var selectedMonitor
    property var monitors
    property var filteredMonitors: []

    function updateFilteredMonitors() {
        if (!selectedMonitor || !monitors) return

        filteredMonitors = [{ name: "None" }]
        for (let i = 0; i < monitors.length; ++i) {
            if (monitors[i].name !== selectedMonitor.name) {
                filteredMonitors.push(monitors[i])
            }
        }
    }

    Component.onCompleted: updateFilteredMonitors()

    ColumnLayout {
        id: root
        spacing: 6

        Label {
            text: "Monitor Details"
            font.pixelSize: 20
            Layout.alignment: Qt.AlignHCenter
        }

        function fieldRow(labelText, bindingProp, onChange) {
            return Qt.createQmlObject(`
                import QtQuick 2.15
                import QtQuick.Layouts 1.15
                import QtQuick.Controls 2.15
                RowLayout {
                    Label { text: "${labelText}"; Layout.minimumWidth: 100 }
                    TextField {
                        Layout.fillWidth: true
                        text: "${bindingProp}"
                        onTextChanged: ${onChange}
                    }
                }`, root)
        }

        // --- ID ---
        RowLayout {
            Label { text: "ID:"; Layout.minimumWidth: 100 }
            Label { text: selectedMonitor ? selectedMonitor.id : "" }
        }

        RowLayout {
            Label { text: "Name:"; Layout.minimumWidth: 100 }
            Label { text: selectedMonitor ? selectedMonitor.name : "" }
        }

        RowLayout {
            Label { text: "Description:"; Layout.minimumWidth: 100 }
            Label { text: selectedMonitor ? selectedMonitor.description : "" }
        }

        RowLayout {
            Label { text: "Make:"; Layout.minimumWidth: 100 }
            Label { text: selectedMonitor ? selectedMonitor.make : "" }
        }

        RowLayout {
            Label { text: "Model:"; Layout.minimumWidth: 100 }
            Label { text: selectedMonitor ? selectedMonitor.model : "" }
        }

        RowLayout {
            Label { text: "Serial:"; Layout.minimumWidth: 100 }
            Label { text: selectedMonitor ? selectedMonitor.serial : "" }
        }

        // --- Editable values (Width, Height, etc.) ---
        MonitorNumericField {
            label: "Width"
            fieldValue: selectedMonitor?.width ?? 0
            editable: !!selectedMonitor
            onValueChanged: if (selectedMonitor) selectedMonitor.width = newValue
        }

        MonitorNumericField {
            label: "Height"
            fieldValue: selectedMonitor?.height ?? 0
            editable: !!selectedMonitor
            onValueChanged: if (selectedMonitor) selectedMonitor.height = newValue
        }

        MonitorNumericField {
            label: "Refresh Rate"
            fieldValue: selectedMonitor?.refreshRate ?? 0
            editable: !!selectedMonitor
            onValueChanged: if (selectedMonitor) selectedMonitor.refreshRate = newValue
        }
        MonitorNumericField {
            label: "X"
            fieldValue: selectedMonitor?.positionX ?? 0
            editable: !!selectedMonitor
            onValueChanged: if (selectedMonitor) selectedMonitor.positionX = newValue
        }

        MonitorNumericField {
            label: "Y"
            fieldValue: selectedMonitor?.positionY ?? 0
            editable: !!selectedMonitor
            onValueChanged: if (selectedMonitor) selectedMonitor.positionY = newValue
        }

        // --- Mode Selection ---
        RowLayout {
            Label { text: "Mode:"; Layout.minimumWidth: 100 }
            ComboBox {
                Layout.fillWidth: true
                model: selectedMonitor ? selectedMonitor.availableModes : []
                Component.onCompleted: {
                    if (selectedMonitor)
                        currentIndex = model.indexOf(selectedMonitor.generateCurrentMode())
                }
                onCurrentIndexChanged: {
                    if (selectedMonitor && currentIndex >= 0)
                        selectedMonitor.applyModeString(model[currentIndex])
                }
            }
        }

        // --- Transform ---
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
                    if (selectedMonitor)
                        currentIndex = model.findIndex(v => v.value === selectedMonitor.transform)
                }
                onCurrentIndexChanged: {
                    if (selectedMonitor)
                        selectedMonitor.transform = model[currentIndex].value
                }
            }
        }

        // --- Mirror Of ---
        RowLayout {
            Label { text: "Mirror of:"; Layout.minimumWidth: 100 }
            ComboBox {
                Layout.fillWidth: true
                model: filteredMonitors
                textRole: "name"
                Component.onCompleted: {
                    if (selectedMonitor) {
                        const index = filteredMonitors.findIndex(m => m.name === selectedMonitor.mirrorOf)
                        currentIndex = index >= 0 ? index : 0
                    }
                }
                onCurrentIndexChanged: {
                    if (selectedMonitor) {
                        const value = filteredMonitors[currentIndex].name
                        selectedMonitor.mirrorOf = value === "None" ? null : value
                    }
                }
            }
        }

        // --- Checkboxes ---
        MonitorCheckbox {
            label: "Disabeld"
            enabled: selectedMonitor !== null
            checked: selectedMonitor ? selectedMonitor.disabled : false
            onToggled: checked => {
                if (selectedMonitor) {
                    selectedMonitor.disabled = checked
                }
            }
        }

        MonitorCheckbox {
            label: "DPMS"
            enabled: selectedMonitor !== null
            checked: selectedMonitor ? selectedMonitor.dpmsStatus : false
            onToggled: checked => {
                if (selectedMonitor) {
                    selectedMonitor.dpmsStatus = checked
                }
            }
        }


        // --- Read-only Info ---
        RowLayout {
            Label {
                text: "VRR:"
                Layout.minimumWidth: 100
            }
            Label {
                text: selectedMonitor?.vrr
            }
        }

        RowLayout {
            Label {
                text: "Solitary:"
                Layout.minimumWidth: 100
            }
            Label {
                text: selectedMonitor?.solitary
            }
        }

        RowLayout {
            Label {
                text: "Tearing:"
                Layout.minimumWidth: 100
            }
            Label {
                text: selectedMonitor?.activelyTearing
            }
        }

        RowLayout {
            Label {
                text: "Scanout To:"
                Layout.minimumWidth: 100
            }
            Label {
                text: selectedMonitor?.directScanoutTo
            }
        }

        RowLayout {
            Label {
                text: "Current Format:"
                Layout.minimumWidth: 100
            }
            Label {
                text: selectedMonitor?.currentFormat
            }
        }
    }
}
