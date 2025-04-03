#include "monitor_helpers.h"
#include <algorithm>
#include <vector>

namespace core {

     std::vector<Monitor> MonitorHelpers::removeMonitorByName(std::vector<Monitor> &monitors, const Monitor &monitor){
        monitors.erase(
            std::remove_if(monitors.begin(), monitors.end(), [&](const Monitor& m) {
                return m.getId() == monitor.getId();
            }),
            monitors.end()
        );

        return monitors;
    }
}
