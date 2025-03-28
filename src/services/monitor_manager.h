#pragma once

#include "../core/models/monitor.h"
#include <vector>

namespace core {

class MonitorManager {
public:
    virtual ~MonitorManager() = default;

    virtual std::vector<Monitor> getMonitors() const = 0;
    virtual bool applyMonitorConfiguration(const std::vector<Monitor>& monitors) const = 0;
};

} // namespace core

