#ifndef HYPR_MONITOR_MANAGER
#define HYPR_MONITOR_MANAGER

#include "monitor_manager.h"
#include "../utils/monitor_parser.h"
#include <vector>

class HyprMonitorManager : public MonitorManager {
    private:
        MonitorParser* parser;

    public:
        HyprMonitorManager(MonitorParser* parser);
        std::vector<Monitor> getMonitors() const override;
        bool applyMonitorConfiguration(const std::vector<Monitor>& monitors) override;
};

#endif

