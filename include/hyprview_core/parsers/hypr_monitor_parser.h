#pragma once

#include "hyprview_core/parsers/monitor_parser.h"
#include "hyprview_core/models/monitor.h"

namespace core {

    class HyprMonitorParser : public MonitorParser {
        public:
            virtual auto parseMonitorsFromJson(const std::string& jsonString) -> std::vector<Monitor> override;
    };

} // namespace core
