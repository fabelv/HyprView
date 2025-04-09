import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Item {
    id: preview

    property real scaleFactor: 1.0
    property int xOffset: 0
    property int yOffset: 0

    Layout.preferredWidth: 0.6 * parent.width
    Layout.fillHeight: true

    function recalculateScaleAndOffset() {
        if (monitorManager) {
            scaleFactor = monitorManager.calculatePreviewScaleFactor(width, height, 0.5)
            const offset = monitorManager.calculateOffsetToCenter(scaleFactor, width, height)
            xOffset = offset.x
            yOffset = offset.y
        }
    }

    onWidthChanged: recalculateScaleAndOffset()
    onHeightChanged: recalculateScaleAndOffset()

    Component.onCompleted: recalculateScaleAndOffset()

    Connections {
        target: monitorManager
        function onMonitorsChanged() {
            recalculateScaleAndOffset()
        }
    }


    Repeater {
        model: monitorManager.monitors

        delegate: Item {
            MonitorRectangle {
                id: rect
                monitor: modelData
                scaleFactor: preview.scaleFactor
                xOffset: preview.xOffset
                yOffset: preview.yOffset
            }

            Connections {
                target: modelData
                function onPositionManuallyUpdated() {
                    preview.recalculateScaleAndOffset()
                }
            }
        }
    }

}

