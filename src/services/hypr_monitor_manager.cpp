#include "hypr_monitor_manager.h"
#include <QProcess>
#include <sstream>

HyprMonitorManager::HyprMonitorManager(MonitorParser* parser) : parser(parser) {}

std::vector<Monitor> HyprMonitorManager::getMonitors() const {
    QProcess process;
    process.start("hyprctl", QStringList() << "monitors" << "-j");
    process.waitForFinished();

    QByteArray output = process.readAllStandardOutput();
    return parser->parseMonitorsFromJson(output.toStdString());
}

bool HyprMonitorManager::applyMonitorConfiguration(const std::vector<Monitor>& monitors) {
    for (const auto& monitor : monitors) {
        std::ostringstream command;
        command << "hyprctl keyword monitor "
                << monitor.getName() << ","
                << monitor.getWidth() << "x" << monitor.getHeight() << "@"
                << monitor.getRefreshRate() << ","
                << monitor.getPositionX() << "x" << monitor.getPositionY() << ","
                << monitor.getScale();

        QProcess process;
        process.start(command.str().c_str());
        process.waitForFinished();

        if (process.exitCode() != 0) {
            return false;
        }
    }
    return true;
}

