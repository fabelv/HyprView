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
            scaleFactor = monitorManager.calculatePreviewScaleFactor(0.5, width, height)
            const offset = monitorManager.calculateOffsetToCenter(width, height, 0.5)
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
        model: monitorManager.monitors_

        delegate: Item {
            property int monitorIndex: index

            MonitorRectangle {
                id: rect
                monitor: modelData
                index: index
                scaleFactor: preview.scaleFactor
                xOffset: preview.xOffset
                yOffset: preview.yOffset
            }

            Connections {
                target: modelData
                function onPositionUpdatedByDragAndDrop() {
                    preview.recalculateScaleAndOffset()
                }
            }
        }
    }

}

