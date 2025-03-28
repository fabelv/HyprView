#pragma once

#include "monitor_manager.h"
#include "../core/utils/monitor_parser.h"
#include <vector>

namespace core {

class HyprMonitorManager : public MonitorManager {
private:
    MonitorParser* parser;
    std::vector<Monitor> preUserEditMonitors;

public:
    explicit HyprMonitorManager(MonitorParser* parser);
    std::vector<Monitor> getMonitors() override;
    bool applyMonitorConfiguration(const std::vector<Monitor>& monitors) const override;
    bool revertMonitorConfiguration() const override;
};

} // namespace core
