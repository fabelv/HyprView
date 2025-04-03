#include "monitor_geometry.h"
#include "logger.h"
#include <algorithm>
#include <climits>
#include <cmath>
#include <string>
#include <vector>

namespace core {

    Position MonitorGeometry::getSnappedPosition(const Monitor &dragged, const std::vector<Monitor> &allMonitors){
        return Position(dragged.getPositionX(), dragged.getPositionY());
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
}

