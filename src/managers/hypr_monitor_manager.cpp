#include "hypr_monitor_manager.h"

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include <array>
#include <cstdio>
#include <iomanip>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#include "hyprview_core/utils/logger.h"

namespace core {

HyprMonitorManager::HyprMonitorManager(const std::shared_ptr<MonitorParser>& parser)
    : MonitorManager(parser) {}

auto HyprMonitorManager::scanMonitors() -> void {
    std::string jsonString = fetchMonitorJson();
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

auto HyprMonitorManager::applyMonitorConfiguration(std::vector<Monitor>& monitors) -> bool {
    for (const auto& m : monitors) {
        std::ostringstream cmd;

        if (m.getDisabled()) {
            cmd << "hyprctl keyword monitor " << m.getName() << ",disable";
        } else {
            cmd << "hyprctl keyword monitor " << m.getName() << "," << m.getWidth() << "x"
                << m.getHeight() << "@" << std::fixed << std::setprecision(2) << m.getRefreshRate()
                << "," << m.getPositionX() << "x" << m.getPositionY() << "," << std::fixed
                << std::setprecision(2) << m.getScale();

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

auto HyprMonitorManager::fetchMonitorJson() -> std::string {
    std::array<int, 2> pipefd;
    if (pipe(pipefd.data()) == -1) {
        throw std::runtime_error("pipe failed");
    }

    pid_t pid = fork();
    if (pid == -1) {
        throw std::runtime_error("fork failed");
    }

    if (pid == 0) {
        // Child
        close(pipefd[0]);  // Close read end
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);

        execlp("hyprctl", "hyprctl", "monitors", "-j", static_cast<char*>(nullptr));
        _exit(127);  // exec failed
    }

    // Parent
    close(pipefd[1]);  // Close write end

    std::string output;
    std::array<char, 128> buffer;
    ssize_t count;

    while ((count = read(pipefd[0], buffer.data(), buffer.size())) > 0) {
        output.append(buffer.data(), count);
    }

    close(pipefd[0]);
    waitpid(pid, nullptr, 0);

    return output;
}

auto HyprMonitorManager::executeCommand(const std::string& cmd) -> bool {
    pid_t pid = fork();

    if (pid == 0) {
        // Child
        execlp("sh", "sh", "-c", cmd.c_str(), static_cast<char*>(nullptr));
        _exit(127);  // exec failed
    } else if (pid < 0) {
        return false;  // fork failed
    }

    int status = 0;
    waitpid(pid, &status, 0);
    return WIFEXITED(status) && WEXITSTATUS(status) == 0;
}

}  // namespace core
