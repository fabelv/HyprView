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

        // Editable fields
        RowLayout {
            Label { text: "Name:"; width: 120 }
            TextField {
                Layout.fillWidth: true
                text: selectedMonitor.name
                onTextChanged: selectedMonitor.name = text
            }
        }

        RowLayout {
            Label { text: "Description:"; width: 120 }
            TextField {
                Layout.fillWidth: true
                text: selectedMonitor.description
                onTextChanged: selectedMonitor.description = text
            }
        }

        RowLayout {
            Label { text: "Make:"; width: 120 }
            TextField {
                Layout.fillWidth: true
                text: selectedMonitor.make
                onTextChanged: selectedMonitor.make = text
            }
        }

        RowLayout {
            Label { text: "Model:"; width: 120 }
            TextField {
                Layout.fillWidth: true
                text: selectedMonitor.model
                onTextChanged: selectedMonitor.model = text
            }
        }

        RowLayout {
            Label { text: "Serial:"; width: 120 }
            TextField {
                Layout.fillWidth: true
                text: selectedMonitor.serial
                onTextChanged: selectedMonitor.serial = text
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
            Label { text: "Scale:"; width: 120 }
            Slider {
                Layout.fillWidth: true
                from: 0.5; to: 2.0; stepSize: 0.1
                value: selectedMonitor.scale
                onValueChanged: selectedMonitor.scale = value
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
            info("ID:", selectedMonitor.id);
            info("Width:", selectedMonitor.width);
            info("Height:", selectedMonitor.height);
            info("Refresh Rate:", selectedMonitor.refreshRate);
            info("X:", selectedMonitor.positionX);
            info("Y:", selectedMonitor.positionY);
            info("Transform:", selectedMonitor.transform);
            info("Focused:", selectedMonitor.focused);
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

