#pragma once

#include <string>
#include <vector>

#include "hyprview_core/models/monitor.h"

namespace core {

class MonitorParser {
   public:
    // core methods
    virtual auto parseMonitorsFromJson(const std::string &jsonString) -> std::vector<Monitor> = 0;
};

}  // namespace core
