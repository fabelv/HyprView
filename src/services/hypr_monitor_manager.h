#pragma once

#include <string>
#include <vector>
#include "../core/utils/hypr_monitor_parser.h"

namespace core {

class HyprMonitorManager {
private:
    HyprMonitorParser* parser;
    Monitor selectedMonitor;
    std::vector<Monitor> monitors;
    std::vector<Monitor> preUserEditMonitors;

public:
    explicit HyprMonitorManager(HyprMonitorParser* parser);
       
    void scanMonitors();
    bool applyMonitorConfiguration(const std::vector<Monitor>& monitors) const;
    bool revertMonitorConfiguration() const;
    Monitor* findMonitorByName(const std::string name);
 
    void setSelectedMonitor(Monitor &monitor);

    std::vector<Monitor> getMonitors();
    Monitor getSelectedMonitor();
};
} // namespace core
