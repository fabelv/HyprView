#pragma once

#include <utility>
#include <vector>
#include "hyprview_core/models/monitor.h"

namespace core {

struct Bounds {
    int minX;
    int minY;
    int maxX;
    int maxY;
};

struct Position {
    int x;
    int y;

    Position(int x = 0, int y = 0) : x(x), y(y) {}
};

class MonitorGeometry {
public:
    static Position getSnappedPosition(const Monitor& dragged, const std::vector<Monitor>& allMonitors); 
    static Position calculateCenteredOffset(const std::vector<Monitor>& allMonitors, double scaleFactor, int areaWidth, int areaHeight);
    static double calculatePreviewScaleFactor(int areaWidth, int areaHeight, float marginPercentage, const std::vector<Monitor>& allMonitors);

private:
    static Bounds computeBoundsOffset(const std::vector<Monitor>& allMonitors);
    static std::pair<int, int> findClosestSnap(const Monitor& dragged, const Monitor& other, int& bestDistance);
};

}

