#pragma once

#include <string>
#include <vector>
#include "hyprview_core/utils/hypr_monitor_parser.h"

namespace core {

class HyprMonitorManager {
private:
    HyprMonitorParser* parser;
    Monitor selectedMonitor;
    std::vector<Monitor> currentMonitors;
    std::vector<Monitor> backupMonitors;
    bool applyMonitorConfiguration(std::vector<Monitor> monitors) const;

public:
    explicit HyprMonitorManager(HyprMonitorParser* parser);
    
    void scanMonitors();
    bool applyMonitorConfiguration() const;
    bool revertMonitorConfiguration() const;

    Monitor* findMonitorByName(const std::string& name);
    void setSelectedMonitor(const Monitor& monitor);

    std::vector<Monitor>& getMonitors();
    Monitor getSelectedMonitor() const;
};

} // namespace core

