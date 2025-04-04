import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Item {
    id: preview

    property real scaleFactor: 1.0
    property int xOffset: 0
    property int yOffset: 0

    width: 800
    height: 600

    function recalculateScaleAndOffset() {
        if (monitorManager) {
            scaleFactor = monitorManager.calculateScaleFactorPreview(width, height, 0.5)
            const offset = monitorManager.calculateOffsetToCenter(scaleFactor, width, height)
            xOffset = offset.x
            yOffset = offset.y
        }
    }

    Component.onCompleted: recalculateScaleAndOffset()

    Connections {
        target: monitorManager
        function onMonitorsChanged() {
            recalculateScaleAndOffset()
        }
    }

    Repeater {
        model: monitorManager.monitors

        MonitorRectangle {
            monitor: modelData
            scaleFactor: preview.scaleFactor
            xOffset: preview.xOffset
            yOffset: preview.yOffset
        }
    }
}

