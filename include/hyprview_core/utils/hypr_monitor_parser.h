#pragma once

#include "hyprview_core/models/monitor.h"

namespace core {

class HyprMonitorParser {
public:
    virtual std::vector<Monitor> parseMonitorsFromJson(const std::string& jsonString) const;
};

} // namespace core
