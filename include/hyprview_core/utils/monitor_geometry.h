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
    static Position getSnappedPosition(const Monitor& dragged,
                                       const std::vector<Monitor>& allMonitors, const int currentX,
                                       const int currentY);
    static Position calculateCenteredOffset(const std::vector<Monitor>& allMonitors,
                                            double scaleFactor, int areaWidth, int areaHeight);
    static double calculatePreviewScaleFactor(int areaWidth, int areaHeight, float marginPercentage,
                                              const std::vector<Monitor>& allMonitors);

   private:
    static Bounds computeBoundsOffset(const std::vector<Monitor>& allMonitors);
    static std::pair<int, int> findClosestSnap(int dX1, int dY1, int dW, int dH, int oX1, int oY1,
                                               int oW, int oH, int& bestDistance);
};

}  // namespace core
