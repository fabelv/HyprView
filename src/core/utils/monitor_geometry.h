#pragma once

#include <vector>
#include "../models/monitor.h"

namespace core {

struct Position {
    int x;
    int y;

    Position(int x = 0, int y = 0) : x(x), y(y) {}
};

class MonitorGeometry {
public:
    static Position getSnappedPosition(const Monitor& dragged, const std::vector<Monitor>& allMonitors); 
    static double calculateScaleFactorPreview(const int areaWidth, const int areaHeight, const float marginPercentage, const std::vector<Monitor> &allMonitors);
};

}

