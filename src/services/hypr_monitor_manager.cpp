#include "hypr_monitor_manager.h"
#include <QProcess>
#include <QDebug>

HyprMonitorManager::HyprMonitorManager(MonitorParser* parser)
    : parser(parser) {}

QList<Monitor*> HyprMonitorManager::getMonitors() const {
    QProcess process;
    process.start("hyprctl", QStringList() << "monitors" << "-j");
    process.waitForFinished();

    QString output = QString::fromUtf8(process.readAllStandardOutput());
    return parser->parseMonitorsFromJson(output);
}

bool HyprMonitorManager::applyMonitorConfiguration(const QList<QObject*>& monitors) {
    for (const auto& obj : monitors) {
        auto* monitor = qobject_cast<Monitor*>(obj);
        if (!monitor)
            continue;

        QString cmd = QString("hyprctl keyword monitor %1,%2x%3@%4,%5x%6,%7")
            .arg(monitor->getName())
            .arg(monitor->getWidth())
            .arg(monitor->getHeight())
            .arg(monitor->getRefreshRate(), 0, 'f', 2)
            .arg(monitor->getPositionX())
            .arg(monitor->getPositionY())
            .arg(monitor->getScale(), 0, 'f', 2);

        QProcess process;
        process.start("sh", QStringList() << "-c" << cmd);
        process.waitForFinished();

        if (process.exitCode() != 0) {
            qWarning() << "Failed to apply config for monitor:" << monitor->getName();
            return false;
        }
    }
    return true;
}

