#ifndef MONITOR_MANAGER
#define MONITOR_MANAGER

#include "../models/monitor.h"
#include <vector>

class MonitorManager {
    public:
        virtual ~MonitorManager() = default;

        virtual std::vector<Monitor> getMonitors() const = 0;
        virtual bool applyMonitorConfiguration(const std::vector<Monitor>& monitors) = 0;
};

#endif 
