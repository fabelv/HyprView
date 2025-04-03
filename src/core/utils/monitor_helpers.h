#include <vector>
#include "../models/monitor.h"

namespace core {

class MonitorHelpers {
public:
    static std::vector<Monitor> removeMonitorByName(std::vector<Monitor> &monitors, const Monitor &monitor);
};

}
