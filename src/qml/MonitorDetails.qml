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

    function safeText(val) {
        return (val === undefined || val === null) ? "" : val;
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

        function safeText(prop) {
            return selectedMonitor ? prop : ""
        }

        function safeInt(prop) {
            return selectedMonitor ? parseInt(prop) : 0
        }

        function safeBool(prop) {
            return selectedMonitor ? !!prop : false
        }

        // --- ID ---
        RowLayout {
            Label { text: "ID:"; Layout.minimumWidth: 100 }
            TextField {
                enabled: false
                Layout.fillWidth: true
                text: selectedMonitor ? selectedMonitor.id : ""
            }
        }

        // --- Name ---
        RowLayout {
            Label { text: "Name:"; Layout.minimumWidth: 100 }
            TextField {
                enabled: false
                Layout.fillWidth: true
                text: selectedMonitor ? selectedMonitor.name : ""
            }
        }

        // --- Description ---
        RowLayout {
            Label { text: "Description:"; Layout.minimumWidth: 100 }
            TextField {
                enabled: false
                Layout.fillWidth: true
                text: selectedMonitor ? selectedMonitor.description : ""
            }
        }

        // --- Make ---
        RowLayout {
            Label { text: "Make:"; Layout.minimumWidth: 100 }
            TextField {
                enabled: false
                Layout.fillWidth: true
                text: selectedMonitor ? selectedMonitor.make : ""
            }
        }

        // --- Model ---
        RowLayout {
            Label { text: "Model:"; Layout.minimumWidth: 100 }
            TextField {
                enabled: false
                Layout.fillWidth: true
                text: selectedMonitor ? selectedMonitor.model : ""
            }
        }

        // --- Serial ---
        RowLayout {
            Label { text: "Serial:"; Layout.minimumWidth: 100 }
            TextField {
                enabled: false
                Layout.fillWidth: true
                text: selectedMonitor ? selectedMonitor.serial : ""
            }
        }

        // --- Width & Height ---
        RowLayout {
            Label { text: "Width:"; Layout.minimumWidth: 100 }
            TextField {
                enabled: !!selectedMonitor
                Layout.fillWidth: true
                text: safeText(selectedMonitor?.width)
                onTextChanged: if (selectedMonitor) selectedMonitor.width = parseInt(text)
            }

            Label { text: "Height:"; Layout.minimumWidth: 100 }
            TextField {
                enabled: !!selectedMonitor
                Layout.fillWidth: true
                text: safeText(selectedMonitor?.height)
                onTextChanged: if (selectedMonitor) selectedMonitor.height = parseInt(text)
            }
        }

        // --- Refresh Rate ---
        RowLayout {
            Label { text: "Refresh Rate:"; Layout.minimumWidth: 100 }
            TextField {
                enabled: !!selectedMonitor
                Layout.fillWidth: true
                text: safeText(selectedMonitor?.refreshRate)
                onTextChanged: if (selectedMonitor) selectedMonitor.refreshRate = parseFloat(text)
            }
        }

        // --- Position X / Y ---
        RowLayout {
            Label { text: "X:"; Layout.minimumWidth: 100 }
            TextField {
                enabled: !!selectedMonitor
                Layout.fillWidth: true
                text: safeText(selectedMonitor?.positionX)
                onTextChanged: if (selectedMonitor) selectedMonitor.positionX = parseInt(text)
            }

            Label { text: "Y:"; Layout.minimumWidth: 100 }
            TextField {
                enabled: !!selectedMonitor
                Layout.fillWidth: true
                text: safeText(selectedMonitor?.positionY)
                onTextChanged: if (selectedMonitor) selectedMonitor.positionY = parseInt(text)
            }
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
                    if (selectedMonitor && currentIndex >= 0 && currentIndex < model.length) {
                        selectedMonitor.applyModeString(model[currentIndex])
                    }
                }
            }
        }

        // --- Transform ---
        RowLayout {
            Label { text: "Transform:"; Layout.minimumWidth: 100 }

            ComboBox {
                id: transformCombo
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
                        currentIndex = findIndexByValue(selectedMonitor.transform)
                }

                onCurrentIndexChanged: {
                    if (selectedMonitor)
                        selectedMonitor.transform = model[currentIndex].value
                }

                function findIndexByValue(val) {
                    for (let i = 0; i < model.length; ++i)
                        if (model[i].value === val)
                            return i
                    return 0
                }
            }
        }

        // --- Mirror Of ---
        RowLayout {
            Label { text: "Mirror of:"; Layout.minimumWidth: 100 }
            ComboBox {
                id: mirrorCombo
                Layout.fillWidth: true
                model: filteredMonitors
                textRole: "name"

                Component.onCompleted: {
                    if (selectedMonitor) {
                        const index = filteredMonitors.findIndex(m => m.name === selectedMonitor.mirrorOf)
                        mirrorCombo.currentIndex = index >= 0 ? index : 0
                    }
                }

                onCurrentIndexChanged: {
                    if (selectedMonitor) {
                        const value = filteredMonitors[mirrorCombo.currentIndex].name
                        selectedMonitor.mirrorOf = value === "None" ? null : value
                    }
                }
            }
        }


        // --- Enabled / DPMS ---
        RowLayout {
            Label { text: "Enabled:"; Layout.minimumWidth: 100 }
            CheckBox {
                enabled: !!selectedMonitor
                checked: selectedMonitor ? !selectedMonitor.disabled : false
                onCheckedChanged: if (selectedMonitor) selectedMonitor.disabled = !checked
            }
        }

        RowLayout {
            Label { text: "DPMS:"; Layout.minimumWidth: 100 }
            CheckBox {
                enabled: !!selectedMonitor
                checked: selectedMonitor ? selectedMonitor.dpmsStatus : false
                onCheckedChanged: if (selectedMonitor) selectedMonitor.dpmsStatus = checked
            }
        }

        
        // --- Read-only Info ---
        function info(label, value) {
            return Qt.createQmlObject(`
                import QtQuick 2.15
                import QtQuick.Layouts 1.15
                import QtQuick.Controls 2.15
                RowLayout {
                    Label { text: "${label}"; Layout.minimumWidth: 100 }
                    Label { text: "${value}" }
                }
            `, root)
        }

        Component.onCompleted: {
            if (selectedMonitor) {
                info("VRR:", selectedMonitor.vrr)
                info("Solitary:", selectedMonitor.solitary)
                info("Tearing:", selectedMonitor.activelyTearing)
                info("Scanout To:", selectedMonitor.directScanoutTo)
                info("Current Format:", selectedMonitor.currentFormat)
            }
        }
    }
}

