#include "hyprview_core/models/monitor.h"
#include <string>
#include <vector>
namespace core {

class MonitorHelpers {
public:
    static std::vector<std::string> getAvailableMirrorMonitors(const Monitor &selectedMonitor, const std::vector<Monitor> &monitors);
};

}
