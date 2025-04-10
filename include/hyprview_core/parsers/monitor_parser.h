#pragma once

#include "hyprview_core/models/monitor.h"
#include <string>
#include <vector>

namespace core {

class MonitorParser {
public:
  virtual auto parseMonitorsFromJson(const std::string &jsonString)
      -> std::vector<Monitor> = 0;
};

} // namespace core
