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

auto MonitorManager::getSelectedMonitor() -> Monitor & {
  if (selectedMonitorIndex_ < currentMonitors_.size()) {
    return currentMonitors_.at(selectedMonitorIndex_);
  }

  log(LogLevel::Error, "Out of range: Selected Monitor Index out of range");
  throw std::out_of_range("Selected Monitor Index out of range");
}

auto MonitorManager::setSelectedMonitorIndex(size_t monitorIndex) -> void {
  if (monitorIndex >= currentMonitors_.size()) {
    log(LogLevel::Error, "Invalid Argument: Monitor Index out of range");
    throw std::invalid_argument("Monitor Index out of range");
  }

  selectedMonitorIndex_ = monitorIndex;
}
} // namespace core
