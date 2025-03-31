#pragma once

#include "../models/monitor.h"

namespace core {

class HyprMonitorParser {
public:
    std::vector<Monitor> parseMonitorsFromJson(const std::string& jsonString) const;
};

} // namespace core
