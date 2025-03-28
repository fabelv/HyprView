#pragma once

#include <string>
#include <vector>
#include "../models/monitor.h"

namespace core {

class MonitorParser {
public:
    virtual ~MonitorParser() = default;
    virtual std::vector<Monitor> parseMonitorsFromJson(const std::string& jsonString) const = 0;
};

} // namespace core
