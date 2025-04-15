
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

        scaleFactor = newScale
        xOffset = newOffset.x
        yOffset = newOffset.y
    }

    function connectMonitorSignals() {
        if (!monitorManager?.monitors_)
            return;

        for (let i = 0; i < monitorManager.monitors_.length; ++i) {
            const m = monitorManager.monitors_[i];

            try {
                m.positionUpdatedByDetailsField.disconnect(recalculateScaleAndOffset);
            } catch (e) {}

            try {
                m.positionUpdatedByDragAndDrop.disconnect(recalculateScaleAndOffset);
            } catch (e) {}

            m.positionUpdatedByDetailsField.connect(recalculateScaleAndOffset);
            m.positionUpdatedByDragAndDrop.connect(recalculateScaleAndOffset);
        }
    }

    onWidthChanged: recalculateScaleAndOffset()
    onHeightChanged: recalculateScaleAndOffset()

    Component.onCompleted: {
        connectMonitorSignals()
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
        }
    }
}

