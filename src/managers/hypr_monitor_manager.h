#pragma once

#include "hyprview_core/managers/monitor_manager.h"
#include "hyprview_core/models/monitor.h"
#include "hyprview_core/parsers/monitor_parser.h"
#include <memory>
#include <vector>

namespace core {

    class HyprMonitorManager : public MonitorManager {
        public:
            // constructors
            explicit HyprMonitorManager(std::shared_ptr<MonitorParser> parser);
            ~HyprMonitorManager() override = default;

            // core methods
            auto scanMonitors() -> void override;
            auto applyMonitorConfiguration() -> bool override;
            auto revertMonitorConfiguration() -> bool override;

        private:
            auto applyMonitorConfiguration(std::vector<Monitor> &monitors) -> bool;
    };

} // namespace core

