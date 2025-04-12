#include "hypr_monitor_manager.h"
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
        std::string jsonString = fetchMonitorJson();
        auto monitors = parser_->parseMonitorsFromJson(jsonString);
        setMonitors(monitors);
    }

    auto HyprMonitorManager::fetchMonitorJson() -> std::string {
        std::array<char, 128> buffer;
        std::string jsonString;
        std::unique_ptr<FILE, decltype(&pclose)> pipe(popen("hyprctl monitors -j", "r"), pclose);

        if (!pipe) {
            log(LogLevel::Error, "popen() failed");
            throw std::runtime_error("popen() failed");
        }

        while (fgets(buffer.data(), static_cast<int>(buffer.size()), pipe.get()) != nullptr) {
            jsonString += buffer.data();
        }

        return jsonString;
    }

    auto HyprMonitorManager::applyMonitorConfiguration() -> bool {
        auto currentMonitors = getMonitors();
        return applyMonitorConfiguration(currentMonitors);
    }

    auto HyprMonitorManager::revertMonitorConfiguration() -> bool {
        auto preUserEditMonitors = getPreUserEditMonitors();
        return applyMonitorConfiguration(preUserEditMonitors);
    }

    auto HyprMonitorManager::applyMonitorConfiguration(std::vector<Monitor>& monitors) -> bool {
        for (const auto& m : monitors) {
            std::ostringstream cmd;

            if (m.getDisabled()) {
                cmd << "hyprctl keyword monitor " << m.getName() << ",disable";
            } else {
                cmd << "hyprctl keyword monitor "
                    << m.getName() << ","
                    << m.getWidth() << "x" << m.getHeight() << "@"
                    << std::fixed << std::setprecision(2) << m.getRefreshRate() << ","
                    << m.getPositionX() << "x" << m.getPositionY() << ","
                    << std::fixed << std::setprecision(2) << m.getScale();

                cmd << ", transform, " << static_cast<int>(m.getTransform());
                cmd << ", vrr, " << (m.getVrrEnabled() ? "1" : "0");

                if (!m.getMirrorOf().empty() && m.getMirrorOf() != "none") {
                    cmd << ", mirror, " << m.getMirrorOf();
                }
            }

            std::string cmdStr = cmd.str();
            log(LogLevel::Info, "Running: " + cmdStr);

            if (!executeCommand(cmdStr)) {
                log(LogLevel::Error, "Failed to apply monitor config: " + cmdStr);
                return false;
            }
        }
        return true;
    }

    auto HyprMonitorManager::executeCommand(const std::string& cmd) -> bool {
        return std::system(cmd.c_str()) == 0;
    }

} // namespace core
