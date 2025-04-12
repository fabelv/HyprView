#include "hyprview_core/utils/monitor_helpers.h"
#include "hyprview_core/models/monitor.h"
#include "hyprview_core/utils/logger.h"
#include <stdexcept>
#include <string>
#include <vector>

namespace core {

std::vector<std::string> MonitorHelpers::getAvailableMirrorMonitors(
    const Monitor &selectedMonitor, const std::vector<Monitor> &monitors) {

  if (monitors.empty()) {
    log(LogLevel::Error, "monitors must not be empty");
    throw std::invalid_argument("monitors must not be empty");
  }

  std::vector<std::string> availableMirrorMonitors;

  if (selectedMonitor.getMirrorOf() == "") {
    availableMirrorMonitors.emplace_back("none");
  }

  for (const Monitor &m : monitors) {
    if (m.getName() == selectedMonitor.getName())
      continue;

    availableMirrorMonitors.emplace_back(m.getName());
  }

  if (selectedMonitor.getMirrorOf() != "") {
    availableMirrorMonitors.emplace_back("none");
  }

  return availableMirrorMonitors;
}

} // namespace core
