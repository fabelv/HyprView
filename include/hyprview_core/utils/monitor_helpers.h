#pragma once

#include <string>
#include <vector>

#include "hyprview_core/models/monitor.h"

namespace core {

class MonitorHelpers {
   public:
    static std::vector<std::string> getAvailableMirrorMonitors(
        const Monitor &selectedMonitor, const std::vector<Monitor> &monitors);
};

}  // namespace core
