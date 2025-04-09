#include "hypr_monitor_manager.h"
#include <cstdlib>
#include <sstream>
#include <iomanip>
#include <vector>
#include "hyprview_core/utils/logger.h"

namespace core {

HyprMonitorManager::HyprMonitorManager(HyprMonitorParser* parser)
    : parser(parser) {}

Monitor* HyprMonitorManager::findMonitorByName(const std::string& name) {
    for (auto& monitor : currentMonitors) {
        if (monitor.getName() == name) {
            return &monitor;
        }
    }
    return nullptr;
}

void HyprMonitorManager::scanMonitors() {
    FILE* pipe = popen("hyprctl monitors -j", "r");
    if (!pipe) {
        log(LogLevel::Error, "Failed to run hyprctl command.");
        return;
    }

    std::ostringstream output;
    char buffer[128];
    while (fgets(buffer, sizeof(buffer), pipe)) {
        output << buffer;
    }
    pclose(pipe);

    currentMonitors = parser->parseMonitorsFromJson(output.str());
    backupMonitors = currentMonitors;

    if (!currentMonitors.empty()){
        selectedMonitor = currentMonitors.at(0);
    }
}


bool HyprMonitorManager::applyMonitorConfiguration(std::vector<Monitor> monitors) const {
    for (const auto& m : monitors) {
        std::ostringstream cmd;

        if (m.isDisabled()) {
            cmd << "hyprctl keyword monitor " << m.getName() << ",disable";
        } else {
            cmd << "hyprctl keyword monitor "
                << m.getName() << ","
                << m.getWidth() << "x" << m.getHeight() << "@"
                << std::fixed << std::setprecision(2) << m.getRefreshRate() << ","
                << m.getPositionX() << "x" << m.getPositionY() << ","
                << std::fixed << std::setprecision(2) << m.getScale();

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


bool HyprMonitorManager::applyMonitorConfiguration() const {
    return applyMonitorConfiguration(currentMonitors);
}

bool HyprMonitorManager::revertMonitorConfiguration() const {
    return applyMonitorConfiguration(backupMonitors);
}

void HyprMonitorManager::setSelectedMonitor(const Monitor& monitor) {
    selectedMonitor = monitor;
}

std::vector<Monitor>& HyprMonitorManager::getMonitors() {
    return currentMonitors;
}

Monitor& HyprMonitorManager::getSelectedMonitor() {
    return selectedMonitor;
}

} // namespace core

