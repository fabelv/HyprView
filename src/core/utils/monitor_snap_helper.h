#pragma once

#include <QPoint>
#include <vector>
#include "../models/monitor.h"

namespace core {

class MonitorSnapHelper {
public:
    static QPoint getSnappedPosition(const Monitor& dragged,
                                     const std::vector<Monitor>& allMonitors,
                                     int snapThreshold = 20); 
};

}

