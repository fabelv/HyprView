#include "monitor_geometry.h"
#include "monitor_helpers.h"
#include "logger.h"
#include <algorithm>
#include <climits>
#include <cmath>
#include <string>
#include <vector>

namespace core {


    Position MonitorGeometry::getSnappedPosition(
        const Monitor& dragged,
        const std::vector<Monitor>& allMonitors)
    {
        auto monitors = allMonitors;
        auto others = core::MonitorHelpers::removeMonitorByName(monitors, dragged);

        int draggedX = dragged.getPositionX();
        int draggedY = dragged.getPositionY();
        int draggedWidth = dragged.getWidth();
        int draggedHeight = dragged.getHeight();

        Position bestPosition = { draggedX, draggedY };
        int minDistance = std::numeric_limits<int>::max();

        for (const auto& other : others) {
            int otherX = other.getPositionX();
            int otherY = other.getPositionY();
            int otherWidth = other.getWidth();
            int otherHeight = other.getHeight();

            // Snap LEFT of dragged to RIGHT of other
            {
                int x = otherX + otherWidth;
                int y = draggedY;
                int dist = std::abs((draggedX) - (otherX + otherWidth));
                if (dist < minDistance) {
                    minDistance = dist;
                    bestPosition = { x, y };
                }
            }

            // Snap RIGHT of dragged to LEFT of other
            {
                int x = otherX - draggedWidth;
                int y = draggedY;
                int dist = std::abs((draggedX + draggedWidth) - otherX);
                if (dist < minDistance) {
                    minDistance = dist;
                    bestPosition = { x, y };
                }
            }

            // Snap TOP of dragged to BOTTOM of other
            {
                int x = draggedX;
                int y = otherY + otherHeight;
                int dist = std::abs((draggedY) - (otherY + otherHeight));
                if (dist < minDistance) {
                    minDistance = dist;
                    bestPosition = { x, y };
                }
            }

            // Snap BOTTOM of dragged to TOP of other
            {
                int x = draggedX;
                int y = otherY - draggedHeight;
                int dist = std::abs((draggedY + draggedHeight) - otherY);
                if (dist < minDistance) {
                    minDistance = dist;
                    bestPosition = { x, y };
                }
            }
        }

        return bestPosition;
    }


    double MonitorGeometry::calculateScaleFactorPreview(const int areaWidth, const int areaHeight, const float marginPercent, const std::vector<Monitor> &allMonitors){
        int minX = INT_MAX;
        int minY = INT_MAX;
        int maxX = INT_MIN;
        int maxY = INT_MIN;

        for(Monitor m : allMonitors){
           minX = std::min(m.getPositionX(), minX);
           minY = std::min(m.getPositionY(), minY);
           maxX = std::max(m.getPositionX() + m.getWidth(), maxX);
           maxY = std::max(m.getPositionY() + m.getHeight(), maxY);
        }

        int totalWidth = maxX - minX;
        int totalHeight = maxY - minY;

        double scaleX = (areaWidth * marginPercent) / totalWidth;
        double scaleY = (areaHeight * marginPercent) / totalHeight;

        return std::min(scaleX, scaleY);
    }

    Position MonitorGeometry::calculatePositionToCenterOffset(const std::vector<Monitor> &allMonitors, double scaleFactor, int width, int height){
        int minX = INT_MAX;
        int minY = INT_MAX;
        int maxX = INT_MIN;
        int maxY = INT_MIN;

        for(Monitor m : allMonitors){
           minX = std::min(m.getPositionX(), minX);
           minY = std::min(m.getPositionY(), minY);
           maxX = std::max(m.getPositionX() + m.getWidth(), maxX);
           maxY = std::max(m.getPositionY() + m.getHeight(), maxY);
        }

        int totalWidth = (maxX - minX) * scaleFactor;
        int totalHeight = (maxY - minY) * scaleFactor;

        double rightMargin = width - totalWidth;
        double bottomMargin = height - totalHeight;

        return Position(rightMargin / 2, bottomMargin / 2);
    }
}

