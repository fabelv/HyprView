
import QtQuick
import QtQuick.Controls

Item {
    id: preview
    width: 600
    height: 500

    property real zoom: 1.0

    Flickable {
        id: flick
        anchors.fill: parent
        clip: true

        contentWidth: canvas.width * zoom
        contentHeight: canvas.height * zoom

        Item {
            id: canvas
            width: 4000
            height: 4000
            scale: zoom
            transformOrigin: Item.TopLeft

            Repeater {
                model: monitorManager.monitors

                MonitorRectangle {
                    monitor: modelData
                    x: modelData.positionX
                    y: modelData.positionY
                }
            }
        }
    }

    WheelHandler {
        id: wheelZoom
        target: preview
        onWheel: (event) => {
            const factor = event.angleDelta.y > 0 ? 1.1 : 0.9
            zoom = Math.max(0.1, Math.min(3.0, zoom * factor))
        }
    }

    // This ensures the zoom calculation runs after the layout is finalized
    onVisibleChanged: {
        if (visible && preview.height > 0) {
            zoom = computeZoomToFitMonitors()
            console.log(`[ZoomFit] Zoom set after visible=true: ${zoom}`)
        }
    }

    onHeightChanged: {
        if (preview.height > 0 && zoom === 1.0) {
            zoom = computeZoomToFitMonitors()
            console.log(`[ZoomFit] Zoom set after height known: ${zoom}`)
        }
    }

    Connections {
        target: monitorManager
        function onMonitorsChanged() {
            zoom = computeZoomToFitMonitors()
            console.log(`[ZoomFit] Zoom updated after monitor change: ${zoom}`)
        }
    }

    function computeZoomToFitMonitors() {
        const monitors = monitorManager.monitors
        if (!monitors || monitors.length === 0) {
            console.warn("[ZoomFit] No monitors found.")
            return 1.0
        }

        console.log("[ZoomFit] Found", monitors.length, "monitor(s)")

        let [minX, minY, maxX, maxY] = [Number.MAX_VALUE, Number.MAX_VALUE, Number.MIN_VALUE, Number.MIN_VALUE]

        for (let i = 0; i < monitors.length; ++i) {
            const m = monitors[i]
            console.log(`[ZoomFit] Monitor ${i}: pos(${m.positionX}, ${m.positionY}), size(${m.width}x${m.height})`)
            minX = Math.min(minX, m.positionX)
            minY = Math.min(minY, m.positionY)
            maxX = Math.max(maxX, m.positionX + m.width)
            maxY = Math.max(maxY, m.positionY + m.height)
        }

        const boundingWidth = maxX - minX
        const boundingHeight = maxY - minY

        console.log("[ZoomFit] Bounding box:")
        console.log(`          Top-Left: (${minX}, ${minY})`)
        console.log(`          Bottom-Right: (${maxX}, ${maxY})`)
        console.log(`[ZoomFit] Bounding size: ${boundingWidth} x ${boundingHeight}`)
        console.log(`[ZoomFit] Preview size: ${preview.width} x ${preview.height}`)

        if (boundingWidth <= 0 || boundingHeight <= 0) {
            console.warn("[ZoomFit] Invalid bounding box. Using zoom = 1.0")
            return 1.0
        }

        const zoomX = preview.width / boundingWidth
        const zoomY = preview.height / boundingHeight
        const result = Math.min(zoomX, zoomY)

        console.log(`[ZoomFit] ZoomX: ${zoomX.toFixed(3)}, ZoomY: ${zoomY.toFixed(3)} → Final Zoom: ${result.toFixed(3)}`)
        return result / 2
    }
}

