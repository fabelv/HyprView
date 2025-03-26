import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ColumnLayout {
    spacing: 10

    Label {
        text: "Monitor Details"
        font.pixelSize: 20
    }

        Component.onCompleted: console.log("🚀 MonitorDetails QML loaded")

    TextField {
        Layout.fillWidth: true
        text: selectedMonitor.name
        onTextChanged: selectedMonitor.name = text
    }

    ComboBox {
        Layout.fillWidth: true
        model: selectedMonitor.availableModes
        currentIndex: model.indexOf(selectedMonitor.currentFormat)
        onCurrentIndexChanged: selectedMonitor.currentFormat = model[currentIndex]
    }

    Slider {
        Layout.fillWidth: true
        from: 0.5; to: 2.0; stepSize: 0.1
        value: selectedMonitor.scale
        onValueChanged: selectedMonitor.scale = value
    }

    CheckBox {
        text: "Enable monitor"
        checked: !selectedMonitor.disabled
        onCheckedChanged: selectedMonitor.disabled = !checked
    }

    Button {
        text: "Apply"
        onClicked: {
            console.log("Apply clicked for", selectedMonitor.name)
            // hook into backend if needed
        }
    }
}

