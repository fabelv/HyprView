#include "hypr_monitor_manager.h"
#include <QProcess>

HyprMonitorManager::HyprMonitorManager(MonitorParser* parser)
    : parser(parser) {}

QList<Monitor*> HyprMonitorManager::getMonitors() const {
    QProcess process;
    process.start("hyprctl", QStringList() << "monitors" << "-j");
    process.waitForFinished();

    QString output = QString::fromUtf8(process.readAllStandardOutput());
    return parser->parseMonitorsFromJson(output);
}

bool HyprMonitorManager::applyMonitorConfiguration(const QList<Monitor*>& monitors) {
    for (const auto& monitor : monitors) {
        QString cmd = QString("hyprctl keyword monitor %1,%2x%3@%4,%5x%6,%7")
            .arg(monitor->getName())
            .arg(monitor->getWidth())
            .arg(monitor->getHeight())
            .arg(monitor->getRefreshRate())
            .arg(monitor->getPositionX())
            .arg(monitor->getPositionY())
            .arg(monitor->getScale());

        QProcess process;
        process.start(cmd);
        process.waitForFinished();

        if (process.exitCode() != 0) {
            return false;
        }
    }
    return true;
}

