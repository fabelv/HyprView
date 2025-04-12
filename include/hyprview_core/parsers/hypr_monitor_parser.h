#pragma once

#include "hyprview_core/models/monitor.h"
#include "hyprview_core/parsers/monitor_parser.h"
#include <nlohmann/json_fwd.hpp>
#include <optional>

namespace core {

class HyprMonitorParser : public MonitorParser {
public:
  virtual auto parseMonitorsFromJson(const std::string &jsonString)
      -> std::vector<Monitor> override;

private:
  virtual auto
  parseSingleMonitor(const nlohmann::json &obj) -> std::optional<Monitor>;
};

} // namespace core
