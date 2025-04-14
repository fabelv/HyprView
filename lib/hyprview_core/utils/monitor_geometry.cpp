#include "hyprview_core/utils/monitor_geometry.h"

#include <algorithm>
#include <climits>
#include <cmath>
#include <string>
#include <vector>

#include "hyprview_core/models/monitor.h"
#include "hyprview_core/utils/logger.h"

namespace core {

Position MonitorGeometry::getSnappedPosition(const Monitor& dragged,
                                             const std::vector<Monitor>& allMonitors,
                                             const int currentX, const int currentY) {
    if (allMonitors.empty() || allMonitors.size() == 1) {
        log(LogLevel::Debug, "No other monitors to snap to.");
        return {currentX, currentY};
    }

    int bestDx = 0;
    int bestDy = 0;
    int bestDistance = INT_MAX;

    const int draggedW = dragged.getWidth();
    const int draggedH = dragged.getHeight();

    log(LogLevel::Debug, "[SNAP] Dragged monitor: " + dragged.getName() +
                         " @ (" + std::to_string(currentX) + ", " + std::to_string(currentY) + 
                         "), size: " + std::to_string(draggedW) + "x" + std::to_string(draggedH) + ")");

    for (const Monitor& other : allMonitors) {
        if (&other == &dragged) continue;

        log(LogLevel::Debug, "  → Checking against monitor: " + other.getName() +
                             " @ (" + std::to_string(other.getPositionX()) + ", " + std::to_string(other.getPositionY()) + 
                             "), size: " + std::to_string(other.getWidth()) + "x" + std::to_string(other.getHeight()) + ")");

        auto [dx, dy] = findClosestSnap(
            currentX, currentY, draggedW, draggedH,
            other.getPositionX(), other.getPositionY(), other.getWidth(), other.getHeight(),
            bestDistance
        );

        if (dx != 0 || dy != 0) {
            log(LogLevel::Debug, "    → Snap delta from " + other.getName() + ": dx=" + std::to_string(dx) + ", dy=" + std::to_string(dy));
            bestDx = dx;
            bestDy = dy;
        }
    }

    int finalX = currentX + bestDx;
    int finalY = currentY + bestDy;

    log(LogLevel::Debug, "[SNAP] Final snapped position: X=" + std::to_string(finalX) + ", Y=" + std::to_string(finalY));
    return {finalX, finalY};
}


std::pair<int, int> MonitorGeometry::findClosestSnap(
    int dX1, int dY1, int dW, int dH,
    int oX1, int oY1, int oW, int oH,
    int& bestDistance
) {
    int dx = 0;
    int dy = 0;

    int dX2 = dX1 + dW;
    int dY2 = dY1 + dH;
    int oX2 = oX1 + oW;
    int oY2 = oY1 + oH;

    bool verticalOverlap = dY2 >= oY1 && dY1 <= oY2;
    bool horizontalOverlap = dX2 >= oX1 && dX1 <= oX2;

    bool foundEdgeSnap = false;

    if (verticalOverlap) {
        foundEdgeSnap = true;
        log(LogLevel::Debug, "    verticalOverlap = true");

        int distR2L = std::abs(dX2 - oX1);
        if (distR2L < bestDistance) {
            log(LogLevel::Debug, "      → Right-to-Left edge snap, dist = " + std::to_string(distR2L));
            bestDistance = distR2L;
            dx = oX1 - dX2;
            dy = 0;
        }

        int distL2R = std::abs(dX1 - oX2);
        if (distL2R < bestDistance) {
            log(LogLevel::Debug, "      → Left-to-Right edge snap, dist = " + std::to_string(distL2R));
            bestDistance = distL2R;
            dx = oX2 - dX1;
            dy = 0;
        }
    }

    if (horizontalOverlap) {
        foundEdgeSnap = true;
        log(LogLevel::Debug, "    horizontalOverlap = true");

        int distB2T = std::abs(dY2 - oY1);
        if (distB2T < bestDistance) {
            log(LogLevel::Debug, "      → Bottom-to-Top edge snap, dist = " + std::to_string(distB2T));
            bestDistance = distB2T;
            dx = 0;
            dy = oY1 - dY2;
        }

        int distT2B = std::abs(dY1 - oY2);
        if (distT2B < bestDistance) {
            log(LogLevel::Debug, "      → Top-to-Bottom edge snap, dist = " + std::to_string(distT2B));
            bestDistance = distT2B;
            dx = 0;
            dy = oY2 - dY1;
        }
    }

    if (!foundEdgeSnap) {
        log(LogLevel::Debug, "    No edge overlap — evaluating corner snapping");
        std::vector<std::pair<int, int>> snapCandidates = {
            {oX1 - dX2, oY1 - dY2},
            {oX2 - dX1, oY1 - dY2},
            {oX1 - dX2, oY2 - dY1},
            {oX2 - dX1, oY2 - dY1},
        };

        for (const auto& [cdx, cdy] : snapCandidates) {
            int dist = std::abs(cdx) + std::abs(cdy);
            log(LogLevel::Debug, "      → Corner snap candidate: dx=" + std::to_string(cdx) +
                                 ", dy=" + std::to_string(cdy) + ", dist=" + std::to_string(dist));
            if (dist < bestDistance) {
                bestDistance = dist;
                dx = cdx;
                dy = cdy;
                log(LogLevel::Debug, "        ↳ Selected as best corner snap so far");
            }
        }
    }

    return {dx, dy};
}


double MonitorGeometry::calculatePreviewScaleFactor(int areaWidth, int areaHeight,
                                                    float marginPercent,
                                                    const std::vector<Monitor>& allMonitors) {
    auto [minX, minY, maxX, maxY] = computeBoundsOffset(allMonitors);

    int totalWidth = maxX - minX;
    int totalHeight = maxY - minY;

    double scaleX = (areaWidth * marginPercent) / totalWidth;
    double scaleY = (areaHeight * marginPercent) / totalHeight;

    return std::min(scaleX, scaleY);
}

Position MonitorGeometry::calculateCenteredOffset(const std::vector<Monitor>& allMonitors,
                                                  double scaleFactor, int areaWidth,
                                                  int areaHeight) {
    auto [minX, minY, maxX, maxY] = computeBoundsOffset(allMonitors);

    int scaledWidth = static_cast<int>((maxX - minX) * scaleFactor);
    int scaledHeight = static_cast<int>((maxY - minY) * scaleFactor);

    int offsetX = static_cast<int>((areaWidth - scaledWidth) / 2 - minX * scaleFactor);
    int offsetY = static_cast<int>((areaHeight - scaledHeight) / 2 - minY * scaleFactor);

    return {offsetX, offsetY};
}


Bounds MonitorGeometry::computeBoundsOffset(const std::vector<Monitor>& allMonitors) {
    int minX = INT_MAX;
    int minY = INT_MAX;
    int maxX = INT_MIN;
    int maxY = INT_MIN;

    for (const auto& m : allMonitors) {
        minX = std::min(minX, m.getPositionX());
        minY = std::min(minY, m.getPositionY());
        maxX = std::max(maxX, m.getPositionX() + m.getWidth());
        maxY = std::max(maxY, m.getPositionY() + m.getHeight());
    }

    return {minX, minY, maxX, maxY};
}

}  // namespace core
