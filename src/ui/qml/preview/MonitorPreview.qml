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
        if (!monitorManager) {
            console.warn("[Preview] monitorManager is undefined")
            return
        }

        const prevScale = scaleFactor
        const prevXOffset = xOffset
        const prevYOffset = yOffset

        const newScale = monitorManager.calculatePreviewScaleFactor(width, height, 0.9)
        const newOffset = monitorManager.calculateOffsetToCenter(newScale, width, height)

        // Update properties
        scaleFactor = newScale
        xOffset = newOffset.x
        yOffset = newOffset.y

        console.log(`[Preview] recalculateScaleAndOffset()`)
        console.log(`  scaleFactor: ${prevScale} → ${scaleFactor}`)
        console.log(`  xOffset:     ${prevXOffset} → ${xOffset}`)
        console.log(`  yOffset:     ${prevYOffset} → ${yOffset}`)
    }


    onWidthChanged: {
        recalculateScaleAndOffset()
    }

    onHeightChanged: {
        recalculateScaleAndOffset()
    }

    Component.onCompleted: {
        recalculateScaleAndOffset()
    }

    Connections {
        target: monitorManager
        function onMonitorsChanged() {
            recalculateScaleAndOffset()
        }
    }

    Repeater {
        model: monitorManager?.monitors_

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
                function onPositionUpdatedByDragAndDrop() {
                    preview.recalculateScaleAndOffset()
                }
            }
        }
    }
}

