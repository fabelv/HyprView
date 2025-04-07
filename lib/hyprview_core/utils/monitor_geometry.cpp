#include <algorithm>
#include <climits>
#include <cmath>
#include <string>
#include <vector>
#include "hyprview_core/models/monitor.h"
#include "hyprview_core/utils/monitor_geometry.h"
#include "hyprview_core/utils/logger.h"

namespace core {

Position MonitorGeometry::getSnappedPosition(const Monitor& dragged, const std::vector<Monitor>& allMonitors) {

    if (allMonitors.empty() || allMonitors.size() == 1) {
        log(LogLevel::Debug, "No other monitors to snap to.");
        return Position(0, 0);
    }

    int bestDx = 0, bestDy = 0;
    int bestDistance = INT_MAX;

    for (const Monitor& other : allMonitors) {
        if (&other == &dragged) continue;

        auto [dx, dy] = findClosestSnap(dragged, other, bestDistance);
        if (dx != 0 || dy != 0) {
            bestDx = dx;
            bestDy = dy;
        }
    }

    int finalX = dragged.getPositionX() + bestDx;
    int finalY = dragged.getPositionY() + bestDy;

    log(LogLevel::Debug, "Snapped to X=" + std::to_string(finalX) + " Y=" + std::to_string(finalY));
    return Position(finalX, finalY);
}

std::pair<int, int> MonitorGeometry::findClosestSnap(const Monitor& dragged, const Monitor& other, int& bestDistance) {
    int dx = 0, dy = 0;

    int dX1 = dragged.getPositionX(), dX2 = dX1 + dragged.getWidth();
    int dY1 = dragged.getPositionY(), dY2 = dY1 + dragged.getHeight();
    int oX1 = other.getPositionX(), oX2 = oX1 + other.getWidth();
    int oY1 = other.getPositionY(), oY2 = oY1 + other.getHeight();

    bool verticalOverlap = dY2 > oY1 && dY1 < oY2;
    bool horizontalOverlap = dX2 > oX1 && dX1 < oX2;

    if (verticalOverlap) {
        int distR2L = std::abs(dX2 - oX1);
        if (distR2L < bestDistance) {
            bestDistance = distR2L;
            dx = oX1 - dX2;
            dy = 0;
        }

        int distL2R = std::abs(dX1 - oX2);
        if (distL2R < bestDistance) {
            bestDistance = distL2R;
            dx = oX2 - dX1;
            dy = 0;
        }
    }

    if (horizontalOverlap) {
        int distB2T = std::abs(dY2 - oY1);
        if (distB2T < bestDistance) {
            bestDistance = distB2T;
            dx = 0;
            dy = oY1 - dY2;
        }

        int distT2B = std::abs(dY1 - oY2);
        if (distT2B < bestDistance) {
            bestDistance = distT2B;
            dx = 0;
            dy = oY2 - dY1;
        }
    }

    // NEW: Corner snapping (no overlap)
    std::vector<std::pair<int, int>> snapCandidates = {
        {oX1 - dX2, oY1 - dY2}, // bottom-right to top-left
        {oX2 - dX1, oY1 - dY2}, // bottom-left to top-right
        {oX1 - dX2, oY2 - dY1}, // top-right to bottom-left
        {oX2 - dX1, oY2 - dY1}, // top-left to bottom-right
    };

    for (const auto& [cdx, cdy] : snapCandidates) {
        int dist = std::abs(cdx) + std::abs(cdy); // Manhattan distance
        if (dist < bestDistance) {
            bestDistance = dist;
            dx = cdx;
            dy = cdy;
        }
    }

    return {dx, dy};
}

double MonitorGeometry::calculatePreviewScaleFactor(int areaWidth, int areaHeight, float marginPercent, const std::vector<Monitor>& allMonitors) {
    auto [minX, minY, maxX, maxY] = computeBoundsOffset(allMonitors);

    int totalWidth = maxX - minX;
    int totalHeight = maxY - minY;

    double scaleX = (areaWidth * marginPercent) / totalWidth;
    double scaleY = (areaHeight * marginPercent) / totalHeight;

    return std::min(scaleX, scaleY);
}

Position MonitorGeometry::calculateCenteredOffset(const std::vector<Monitor>& allMonitors, double scaleFactor, int areaWidth, int areaHeight) {
    auto [minX, minY, maxX, maxY] = computeBoundsOffset(allMonitors);
    log(LogLevel::Debug, "minX"+ std::to_string(minX) + " minY" + std::to_string(minY));
    log(LogLevel::Debug, "maxX"+ std::to_string(maxX) + " maxY" + std::to_string(maxY));

    int scaledWidth = static_cast<int>((maxX - minX) * scaleFactor);
    int scaledHeight = static_cast<int>((maxY - minY) * scaleFactor);
    log(LogLevel::Debug, "scaledWidth"+ std::to_string(scaledWidth) + " scaledHeight" + std::to_string(scaledHeight));

    int offsetX = (areaWidth - scaledWidth) / 2;
    int offsetY = (areaHeight - scaledHeight) / 2;

    return Position(offsetX, offsetY);
}

Bounds MonitorGeometry::computeBoundsOffset(const std::vector<Monitor>& allMonitors) {
    int minX = INT_MAX, minY = INT_MAX;
    int maxX = INT_MIN, maxY = INT_MIN;

    for (const auto& m : allMonitors) {
        minX = std::min(minX, m.getPositionX());
        minY = std::min(minY, m.getPositionY());
        maxX = std::max(maxX, m.getPositionX() + m.getWidth());
        maxY = std::max(maxY, m.getPositionY() + m.getHeight());
    }

    return {minX, minY, maxX, maxY};
}

}
