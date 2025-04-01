#include "qml_monitor_manager.h"
#include "../core/utils/logger.h"
#include "../core/utils/monitor_snap_helper.h"
#include "../core/models/monitor.h"
#include "../services/hypr_monitor_manager.h"
#include "qml_monitor.h"

QmlMonitorManager::QmlMonitorManager(core::HyprMonitorManager* coreManager, QObject* parent)
    : QObject(parent), m_coreManager(coreManager), m_selectedMonitor(nullptr)
{
    log(core::LogLevel::Info, "Initializing QmlMonitorManager...");
    scanMonitors();
}


void QmlMonitorManager::scanMonitors() {
    log(core::LogLevel::Info, "Scanning monitors...");

    const auto coreMonitors = m_coreManager->getMonitors();
    m_monitors.clear();

    for (const auto& monitor : coreMonitors) {
        auto* qmlMonitor = new QmlMonitor(monitor);
        m_monitors.append(qmlMonitor);
    }

    m_selectedMonitor = m_monitors.isEmpty() ? nullptr : m_monitors.first();

    log(core::LogLevel::Debug, "Scan found " + std::to_string(m_monitors.size()) + " monitor(s).");

    emit monitorsChanged();
    emit selectedMonitorChanged();
}

QPoint QmlMonitorManager::getSnappedPosition(const QString &monitorName) {
    const auto* dragged = m_coreManager->findMonitorByName(monitorName.toStdString());
    if (!dragged)
        return QPoint(0, 0); // fallback

    const auto& allMonitors = m_coreManager->getMonitors();
    return core::MonitorSnapHelper::getSnappedPosition(*dragged, allMonitors, 0);
}


void QmlMonitorManager::applyMonitorConfiguration() {
    log(core::LogLevel::Info, "Applying monitor configuration...");

    std::vector<core::Monitor> coreMonitors;

    for (auto* monitor: m_monitors) {
        if (monitor)
            coreMonitors.push_back(monitor->internal()); 
    }

    if (!m_coreManager->applyMonitorConfiguration(coreMonitors)) {
        log(core::LogLevel::Error, "Failed to apply monitor configuration.");
    } else {
        log(core::LogLevel::Info, "Monitor configuration applied successfully.");
    }

    emit monitorConfigurationApplied();
}

void QmlMonitorManager::revertMonitorConfiguration() {
    log(core::LogLevel::Info, "Reverting monitor configuration...");

    if (!m_coreManager->revertMonitorConfiguration()) {
        log(core::LogLevel::Error, "Failed to revert monitor configuration.");
    } else {
        log(core::LogLevel::Info, "Monitor configuration reverted successfully.");
    }

    scanMonitors();
}

QList<QmlMonitor*> QmlMonitorManager::getMonitors() const {
    return m_monitors;
}

QmlMonitor* QmlMonitorManager::getSelectedMonitor() const {
    return m_selectedMonitor;
}

void QmlMonitorManager::setSelectedMonitor(QmlMonitor* monitor) {
    m_selectedMonitor = monitor;
    emit selectedMonitorChanged();
}
