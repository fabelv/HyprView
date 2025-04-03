import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Item {
    id: preview

    property real scaleFactor: 1.0

    Component.onCompleted: {
        if (monitorManager) {
            scaleFactor = monitorManager.calculateScaleFactorPreview(800, 600, 0.5)
            console.log("Scale factor (corrected):", scaleFactor)
        }
    }


    Repeater {
        model: monitorManager.monitors

        MonitorRectangle {
            monitor: modelData
            scaleFactor: scaleFactor
        }
    }
}


