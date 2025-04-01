#include "monitor_snap_helper.h"
#include <cmath>

namespace core {

static int distance(int x1, int y1, int x2, int y2) {
    int dx = x1 - x2;
    int dy = y1 - y2;
    return std::sqrt(dx * dx + dy * dy);
}

QPoint MonitorSnapHelper::getSnappedPosition(const Monitor& dragged,
                                             const std::vector<Monitor>& monitors,
                                             int snapThreshold)
{
    QPoint bestSnap = QPoint(dragged.getPositionX() ,dragged.getPositionY());
    int minDist = INT_MAX;

    for (const auto& other : monitors) {
        if (other.getName() == dragged.getName())
            continue;

        std::vector<QPoint> candidates = {
            // Snap left
            {other.getPositionX() - dragged.getWidth(), other.getPositionY()},
            // Snap right
            {other.getPositionX() + other.getWidth(), other.getPositionY()},
            // Snap top
            {other.getPositionX(), other.getPositionY() - dragged.getHeight()},
            // Snap bottom
            {other.getPositionX(), other.getPositionY() + other.getHeight()}
        };

        for (const QPoint& p : candidates) {
            int dist = distance(dragged.getPositionX(), dragged.getPositionY(), p.x(), p.y());
            if (dist < minDist && dist <= snapThreshold) {
                minDist = dist;
                bestSnap = p;
            }
        }
    }

    return bestSnap;
}

}

