#include "hypr_monitor_manager.h"
#include "../core/utils/logger.h"
#include <cstdlib>
#include <sstream>
#include <iomanip>

namespace core {

HyprMonitorManager::HyprMonitorManager(MonitorParser* parser)
    : parser(parser) {}

std::vector<Monitor> HyprMonitorManager::getMonitors() {
    FILE* pipe = popen("hyprctl monitors -j", "r");
    if (!pipe) {
        log(LogLevel::Error, "Failed to run hyprctl command.");
        return {};
    }

    std::ostringstream output;
    char buffer[128];
    while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
        output << buffer;
    }
    pclose(pipe);

    std::vector<Monitor> monitors = parser->parseMonitorsFromJson(output.str());

    preUserEditMonitors = monitors;

    return monitors;
}


bool HyprMonitorManager::applyMonitorConfiguration(const std::vector<Monitor>& monitors) const {
    for (const auto& monitor : monitors) {
        std::ostringstream cmd;
        cmd << "hyprctl keyword monitor "
            << monitor.getName() << ","
            << monitor.getWidth() << "x" << monitor.getHeight() << "@"
            << std::fixed << std::setprecision(2) << monitor.getRefreshRate() << ","
            << monitor.getPositionX() << "x" << monitor.getPositionY() << ","
            << std::fixed << std::setprecision(2) << monitor.getScale();

        // Optional args
        cmd << ", transform, " << static_cast<int>(monitor.getTransform());

        if (!monitor.getMirrorOf().empty()) {
            cmd << ", mirror, " << monitor.getMirrorOf();
        }

        cmd << ", vrr, " << (monitor.isVrrEnabled() ? "1" : "0");

        log(LogLevel::Info, "Running: " + cmd.str());

        int result = std::system(cmd.str().c_str());
        if (result != 0) {
            log(LogLevel::Error, "Failed to apply monitor config: " + cmd.str());
            return false;
        }
    }

    return true;
}

bool HyprMonitorManager::revertMonitorConfiguration() const {
    return applyMonitorConfiguration(this->preUserEditMonitors);
}

} // namespace core

