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
            Label { text: "ID:"; Layout.minimumWidth: 100}
            TextField {
                enabled: false
                Layout.fillWidth: true
                text: selectedMonitor.id
                onTextChanged: selectedMonitor.id = text
            }
        }

        // name
        RowLayout {
            Label { text: "Name:"; Layout.minimumWidth: 100 }
            TextField {
                enabled: false
                Layout.fillWidth: true
                text: selectedMonitor.name
                onTextChanged: selectedMonitor.name = text
            }
        }

        // description
        RowLayout {
            Label { text: "Description:"; Layout.minimumWidth: 100 }
            TextField {
                enabled: false
                Layout.fillWidth: true
                text: selectedMonitor.description
                onTextChanged: selectedMonitor.description = text
            }
        }

        // make
        RowLayout {
            Label { text: "Make:"; Layout.minimumWidth: 100 }
            TextField {
                enabled: false
                Layout.fillWidth: true
                text: selectedMonitor.make
                onTextChanged: selectedMonitor.make = text
            }
        }

        // model
        RowLayout {
            Label { text: "Model:"; Layout.minimumWidth: 100 }
            TextField {
                enabled: false
                Layout.fillWidth: true
                text: selectedMonitor.model
                onTextChanged: selectedMonitor.model = text
            }
        }

        // serial
        RowLayout {
            Label { text: "Serial:"; Layout.minimumWidth: 100 }
            TextField {
                enabled: false
                Layout.fillWidth: true
                text: selectedMonitor.serial
                onTextChanged: selectedMonitor.serial = text
            }
        }

        // width x height
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

        // refreshRate
        RowLayout {
            Label { text: "Refresh Rate:"; Layout.minimumWidth: 100 }
            TextField {
                enabled: false
                Layout.fillWidth: true
                text: selectedMonitor.refreshRate
                onTextChanged: selectedMonitor.refreshRate = text
            }
        }

        // x y position
        RowLayout {
            Label { text: "X:"; Layout.minimumWidth: 100 }
            TextField {
                Layout.fillWidth: true
                text: selectedMonitor.positionX
                onTextChanged: selectedMonitor.positionX = text
            }
            Label { text: "Y:"; Layout.minimumWidth: 100 }
            TextField {
                Layout.fillWidth: true
                text: selectedMonitor.positionY
                onTextChanged: selectedMonitor.positionY = text
            }
        }

        RowLayout {
            Label { text: "Mode:"; Layout.minimumWidth: 100 }
            ComboBox {
                Layout.fillWidth: true
                model: selectedMonitor.availableModes
                currentIndex: model.indexOf(selectedMonitor.currentFormat)
                onCurrentIndexChanged: selectedMonitor.currentFormat = model[currentIndex]
            }
        }

        RowLayout {
            Label { text: "Enabled:"; Layout.minimumWidth: 100 }
            CheckBox {
                checked: !selectedMonitor.disabled
                onCheckedChanged: selectedMonitor.disabled = !checked
            }
        }
        
        RowLayout {
            Label { text: "DPMS:"; Layout.minimumWidth: 100 }
            CheckBox {
                checked: !selectedMonitor.dpmsStatus
                onCheckedChanged: selectedMonitor.dpmsStatus = !checked
            }
        }

        RowLayout {
            Label {
                text: "Transform:"
                Layout.minimumWidth: 100
            }

            ComboBox {
                Layout.fillWidth: true

                model: ListModel {
                    ListElement { text: "normal (no transforms)"; value: 0 }
                    ListElement { text: "90 degrees"; value: 1 }
                    ListElement { text: "180 degrees"; value: 2 }
                    ListElement { text: "270 degrees"; value: 3 }
                    ListElement { text: "flipped"; value: 4 }
                    ListElement { text: "flipped + 90 degrees"; value: 5 }
                    ListElement { text: "flipped + 180 degrees"; value: 6 }
                    ListElement { text: "flipped + 270 degrees"; value: 7 }
                }

                textRole: "text" // what is displayed
                // set currentIndex based on transform value
                Component.onCompleted: {
                    currentIndex = findIndexByValue(selectedMonitor.transform)
                }

                onCurrentIndexChanged: {
                    selectedMonitor.transform = model.get(currentIndex).value
                }

                function findIndexByValue(val) {
                    for (var i = 0; i < model.count; ++i) {
                        if (model.get(i).value === val)
                            return i;
                    }
                    return 0 // fallback
                }
            }
        }

        // Read-only fields (use Label)
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
            info("Transform:", selectedMonitor.transform);
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

