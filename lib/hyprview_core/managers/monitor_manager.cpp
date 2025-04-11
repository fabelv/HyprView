#include "hyprview_core/managers/monitor_manager.h"
#include "hyprview_core/utils/logger.h"

namespace core {

// constructors
MonitorManager::MonitorManager(std::shared_ptr<MonitorParser> parser)
    : parser_(parser) {}

// accessors
auto MonitorManager::getMonitors() -> std::vector<Monitor> & {
  return currentMonitors_;
}

auto MonitorManager::setMonitors(std::vector<Monitor> &monitors) -> void {
  if (monitors.empty()) {
    log(LogLevel::Error,
        "Invalid Argument: Manager cannot manage an empty vector of monitors");
    throw std::invalid_argument(
        "Manager cannot mange an empty vector of monitors");
  }

  currentMonitors_ = monitors;
  preUserEditMonitors_ = monitors;
  selectedMonitorIndex_ = 0;
}

auto MonitorManager::getPreUserEditMonitors() -> std::vector<Monitor> & {
  return preUserEditMonitors_;
}

} // namespace core
