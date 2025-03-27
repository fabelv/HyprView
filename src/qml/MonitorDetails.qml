import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ScrollView {
    ScrollBar.vertical.policy: ScrollBar.AsNeeded

    ColumnLayout {
        id: root
        width: parent.width
        spacing: 6

        Label {
            text: "Monitor Details"
            font.pixelSize: 20
            Layout.alignment: Qt.AlignHCenter
        }

        // id
        RowLayout {
            Label { text: "ID:"; width: 120 }
            TextField {
                enabled: false
                Layout.fillWidth: true
                text: selectedMonitor.id
                onTextChanged: selectedMonitor.id = text
            }
        }

        // name
        RowLayout {
            Label { text: "Name:"; width: 120 }
            TextField {
                enabled: false
                Layout.fillWidth: true
                text: selectedMonitor.name
                onTextChanged: selectedMonitor.name = text
            }
        }

        // description
        RowLayout {
            Label { text: "Description:"; width: 120 }
            TextField {
                enabled: false
                Layout.fillWidth: true
                text: selectedMonitor.description
                onTextChanged: selectedMonitor.description = text
            }
        }

        // make
        RowLayout {
            Label { text: "Make:"; width: 120 }
            TextField {
                enabled: false
                Layout.fillWidth: true
                text: selectedMonitor.make
                onTextChanged: selectedMonitor.make = text
            }
        }

        // model
        RowLayout {
            Label { text: "Model:"; width: 120 }
            TextField {
                enabled: false
                Layout.fillWidth: true
                text: selectedMonitor.model
                onTextChanged: selectedMonitor.model = text
            }
        }

        // serial
        RowLayout {
            Label { text: "Serial:"; width: 120 }
            TextField {
                enabled: false
                Layout.fillWidth: true
                text: selectedMonitor.serial
                onTextChanged: selectedMonitor.serial = text
            }
        }

        // width x height
        RowLayout {
            Label { text: "Width:"; width: 120 }
            TextField {
                enabled: false
                Layout.fillWidth: true
                text: selectedMonitor.width
                onTextChanged: selectedMonitor.width = text
            }
            Label { text: "Height:"; width: 120 }
            TextField {
                enabled: false
                Layout.fillWidth: true
                text: selectedMonitor.height
                onTextChanged: selectedMonitor.height = text
            }

        }

        // refreshRate
        RowLayout {
            Label { text: "Refresh Rate:"; width: 120 }
            TextField {
                enabled: false
                Layout.fillWidth: true
                text: selectedMonitor.refreshRate
                onTextChanged: selectedMonitor.refreshRate = text
            }
        }

        // x y position
        RowLayout {
            Label { text: "X:"; width: 120 }
            TextField {
                Layout.fillWidth: true
                text: selectedMonitor.positionX
                onTextChanged: selectedMonitor.positionX = text
            }
            Label { text: "Y:"; width: 120 }
            TextField {
                Layout.fillWidth: true
                text: selectedMonitor.positionY
                onTextChanged: selectedMonitor.positionY = text
            }
        }

        RowLayout {
            Label { text: "Mode:"; width: 120 }
            ComboBox {
                Layout.fillWidth: true
                model: selectedMonitor.availableModes
                currentIndex: model.indexOf(selectedMonitor.currentFormat)
                onCurrentIndexChanged: selectedMonitor.currentFormat = model[currentIndex]
            }
        }

        RowLayout {
            Label { text: "Enabled:"; width: 120 }
            CheckBox {
                checked: !selectedMonitor.disabled
                onCheckedChanged: selectedMonitor.disabled = !checked
            }
        }

        // Read-only fields (use Label)
        function info(label, value) {
            return Qt.createQmlObject(`
                import QtQuick 2.15; import QtQuick.Layouts 1.15; import QtQuick.Controls 2.15;
                RowLayout {
                    Label { text: "${label}"; width: 120 }
                    Label { text: "${value}" }
                }
            `, root);
        }

        Component.onCompleted: {
            info("Transform:", selectedMonitor.transform);
            info("DPMS:", selectedMonitor.dpmsStatus);
            info("VRR:", selectedMonitor.vrr);
            info("Solitary:", selectedMonitor.solitary);
            info("Tearing:", selectedMonitor.activelyTearing);
            info("Scanout To:", selectedMonitor.directScanoutTo);
            info("Mirror Of:", selectedMonitor.mirrorOf);
            info("Current Format:", selectedMonitor.currentFormat);
        }

        Button {
            text: "Apply"
            Layout.alignment: Qt.AlignHCenter
            onClicked: {
                console.log("Apply clicked for", selectedMonitor.name)
                // hook into backend if needed
            }
        }
    }
}

