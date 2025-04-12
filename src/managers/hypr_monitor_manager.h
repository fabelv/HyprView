#pragma once

#include "hyprview_core/managers/monitor_manager.h"
#include "hyprview_core/models/monitor.h"
#include "hyprview_core/parsers/monitor_parser.h"
#include <memory>
#include <string>
#include <vector>

namespace core {

class HyprMonitorManager : public MonitorManager {
public:
  explicit HyprMonitorManager(std::shared_ptr<MonitorParser> parser);
  ~HyprMonitorManager() override = default;

  auto scanMonitors() -> void override;
  auto applyMonitorConfiguration() -> bool override;
  auto revertMonitorConfiguration() -> bool override;

protected:
  // Extracted for testability
  virtual auto fetchMonitorJson() -> std::string;
  virtual auto executeCommand(const std::string &cmd) -> bool;

private:
  auto applyMonitorConfiguration(std::vector<Monitor> &monitors) -> bool;
};

} // namespace core
