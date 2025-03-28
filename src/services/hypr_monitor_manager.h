#pragma once

#include "monitor_manager.h"
#include "../core/utils/monitor_parser.h"

namespace core {

class HyprMonitorManager : public MonitorManager {
private:
    MonitorParser* parser;

public:
    explicit HyprMonitorManager(MonitorParser* parser);
    std::vector<Monitor> getMonitors() const override;
    bool applyMonitorConfiguration(const std::vector<Monitor>& monitors) const override;
};

} // namespace core
