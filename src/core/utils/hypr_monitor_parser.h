#pragma once

#include "monitor_parser.h"
#include "../models/monitor.h"

namespace core {

class HyprMonitorParser : public MonitorParser {
public:
    std::vector<Monitor> parseMonitorsFromJson(const std::string& jsonString) const override;
};

} // namespace core
