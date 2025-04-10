#include "hypr_monitor_manager.h"
#include "hyprview_core/models/monitor.h"
#include "hyprview_core/utils/logger.h"
#include <array>
#include <cstdio>
#include <iomanip>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

namespace core {

HyprMonitorManager::HyprMonitorManager(std::shared_ptr<MonitorParser> parser)
    : MonitorManager(parser) {}

auto HyprMonitorManager::scanMonitors() -> void {
  std::array<char, 128> buffer;
  std::string jsonString;
  std::unique_ptr<FILE, decltype(&pclose)> pipe(
      popen("hyprctl monitors -j", "r"), pclose);

  if (!pipe) {
    log(LogLevel::Error, "popen() failed");
    throw std::runtime_error("popen() failed");
  }

  while (fgets(buffer.data(), static_cast<int>(buffer.size()), pipe.get()) !=
         nullptr) {
    jsonString += buffer.data();
  }

  auto monitors = parser_->parseMonitorsFromJson(jsonString);

  setMonitors(monitors);
}

auto HyprMonitorManager::applyMonitorConfiguration() -> bool {
  auto currentMonitors = getMonitors();
  return applyMonitorConfiguration(currentMonitors);
}

auto HyprMonitorManager::revertMonitorConfiguration() -> bool {
  auto preUserEditMonitors = getPreUserEditMonitors();
  return applyMonitorConfiguration(preUserEditMonitors);
}

auto HyprMonitorManager::applyMonitorConfiguration(
    std::vector<Monitor> &monitors) -> bool {
  for (const auto &m : monitors) {
    std::ostringstream cmd;

    if (m.isDisabled()) {
      cmd << "hyprctl keyword monitor " << m.getName() << ",disable";
    } else {
      cmd << "hyprctl keyword monitor " << m.getName() << "," << m.getWidth()
          << "x" << m.getHeight() << "@" << std::fixed << std::setprecision(2)
          << m.getRefreshRate() << "," << m.getPositionX() << "x"
          << m.getPositionY() << "," << std::fixed << std::setprecision(2)
          << m.getScale();

      // Optional fields
      cmd << ", transform, " << static_cast<int>(m.getTransform());
      cmd << ", vrr, " << (m.isVrrEnabled() ? "1" : "0");

      if (!m.getMirrorOf().empty() || m.getMirrorOf() != "none") {
        cmd << ", mirror, " << m.getMirrorOf();
      }
    }

    std::string cmdStr = cmd.str();
    log(LogLevel::Info, "Running: " + cmdStr);

    if (std::system(cmdStr.c_str()) != 0) {
      log(LogLevel::Error, "Failed to apply monitor config: " + cmdStr);
      return false;
    }
  }
  return true;
}

} // namespace core
