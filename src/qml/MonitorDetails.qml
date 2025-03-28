import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import HyprView 1.0

ScrollView {
    id: scrollView
    ScrollBar.vertical.policy: ScrollBar.AsNeeded

    property var filteredMonitors: []

    function updateFilteredMonitors() {
        filteredMonitors = [{ name: "None" }]
        for (let i = 0; i < monitors.length; ++i) {
            if (monitors[i].name !== selectedMonitor.name) {
                filteredMonitors.push(monitors[i])
            }
        }
    }

    Component.onCompleted: {
        updateFilteredMonitors()
    }

    ColumnLayout {
        id: root
        spacing: 6

        Label {
            text: "Monitor Details"
            font.pixelSize: 20
            Layout.alignment: Qt.AlignHCenter
        }

        // ID
        RowLayout {
            Label { text: "ID:"; Layout.minimumWidth: 100 }
            TextField {
                enabled: false
                Layout.fillWidth: true
                text: selectedMonitor.id
                onTextChanged: selectedMonitor.id = text
            }
        }

        // Name
        RowLayout {
            Label { text: "Name:"; Layout.minimumWidth: 100 }
            TextField {
                enabled: false
                Layout.fillWidth: true
                text: selectedMonitor.name
                onTextChanged: selectedMonitor.name = text
            }
        }

        // Description
        RowLayout {
            Label { text: "Description:"; Layout.minimumWidth: 100 }
            TextField {
                enabled: false
                Layout.fillWidth: true
                text: selectedMonitor.description
                onTextChanged: selectedMonitor.description = text
            }
        }

        // Make
        RowLayout {
            Label { text: "Make:"; Layout.minimumWidth: 100 }
            TextField {
                enabled: false
                Layout.fillWidth: true
                text: selectedMonitor.make
                onTextChanged: selectedMonitor.make = text
            }
        }

        // Model
        RowLayout {
            Label { text: "Model:"; Layout.minimumWidth: 100 }
            TextField {
                enabled: false
                Layout.fillWidth: true
                text: selectedMonitor.model
                onTextChanged: selectedMonitor.model = text
            }
        }

        // Serial
        RowLayout {
            Label { text: "Serial:"; Layout.minimumWidth: 100 }
            TextField {
                enabled: false
                Layout.fillWidth: true
                text: selectedMonitor.serial
                onTextChanged: selectedMonitor.serial = text
            }
        }

        // Width x Height
        RowLayout {
            Label { text: "Width:"; Layout.minimumWidth: 100 }
            TextField {
                enabled: false
                Layout.fillWidth: true
                text: selectedMonitor.width
                onTextChanged: selectedMonitor.width = text
            }
            Label { text: "Height:"; Layout.minimumWidth: 100 }
            TextField {
                enabled: false
                Layout.fillWidth: true
                text: selectedMonitor.height
                onTextChanged: selectedMonitor.height = text
            }
        }

        // Refresh Rate
        RowLayout {
            Label { text: "Refresh Rate:"; Layout.minimumWidth: 100 }
            TextField {
                enabled: false
                Layout.fillWidth: true
                text: selectedMonitor.refreshRate
                onTextChanged: selectedMonitor.refreshRate = text
            }
        }

        // X / Y Position
        RowLayout {
            Label { text: "X:"; Layout.minimumWidth: 100 }
            TextField {
                Layout.fillWidth: true
                text: selectedMonitor.positionX
                onTextChanged: selectedMonitor.positionX = parseInt(text)
            }
            Label { text: "Y:"; Layout.minimumWidth: 100 }
            TextField {
                Layout.fillWidth: true
                text: selectedMonitor.positionY
                onTextChanged: selectedMonitor.positionY = parseInt(text)
            }
        }

        // Mode selection

        RowLayout {
            Label { text: "Mode:"; Layout.minimumWidth: 100 }

            ComboBox {
                Layout.fillWidth: true
                model: selectedMonitor.availableModes

                Component.onCompleted: {
                    currentIndex = model.indexOf(selectedMonitor.generateCurrentMode())
                }

                
                onCurrentIndexChanged: {
                    if (currentIndex >= 0 && currentIndex < model.length) {
                        selectedMonitor.applyModeString(model[currentIndex])
                    }
                }
            }
        }


        // Enabled
        RowLayout {
            Label { text: "Enabled:"; Layout.minimumWidth: 100 }
            CheckBox {
                checked: !selectedMonitor.disabled
                onCheckedChanged: selectedMonitor.disabled = !checked
            }
        }

        // DPMS
        RowLayout {
            Label { text: "DPMS:"; Layout.minimumWidth: 100 }
            CheckBox {
                checked: !selectedMonitor.dpmsStatus
                onCheckedChanged: selectedMonitor.dpmsStatus = !checked
            }
        }

        // Transform
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
                    currentIndex = findIndexByValue(selectedMonitor.transform)
                }

                onCurrentIndexChanged: {
                    selectedMonitor.transform = model[currentIndex].value
                }

                function findIndexByValue(val) {
                    for (let i = 0; i < model.length; ++i) {
                        if (model[i].value === val)
                            return i;
                    }
                    return 0
                }
            }
        }

        // Mirror Of
        RowLayout {
            Label { text: "Mirror of:"; Layout.minimumWidth: 100 }

            ComboBox {
                id: mirrorCombo
                Layout.fillWidth: true
                model: filteredMonitors
                textRole: "name"

                Component.onCompleted: {
                    const index = filteredMonitors.findIndex(m => m.name === selectedMonitor.mirrorOf)
                    mirrorCombo.currentIndex = index >= 0 ? index : 0
                }

                onCurrentIndexChanged: {
                    const value = filteredMonitors[mirrorCombo.currentIndex].name
                    selectedMonitor.mirrorOf = value === "None" ? null : value
                    console.log("Mirror set to", selectedMonitor.mirrorOf)
                }
            }
        }

        // Additional Info (Read-only)
        function info(label, value) {
            return Qt.createQmlObject(`
                import QtQuick 2.15; import QtQuick.Layouts 1.15; import QtQuick.Controls 2.15;
                RowLayout {
                    Label { text: "${label}"; Layout.minimumWidth: 100 }
                    Label { text: "${value}" }
                }
            `, root);
        }

        Component.onCompleted: {
            info("VRR:", selectedMonitor.vrr);
            info("Solitary:", selectedMonitor.solitary);
            info("Tearing:", selectedMonitor.activelyTearing);
            info("Scanout To:", selectedMonitor.directScanoutTo);
            info("Current Format:", selectedMonitor.currentFormat);
        }
    }
}

