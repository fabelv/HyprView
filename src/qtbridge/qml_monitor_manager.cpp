#include "qml_monitor_manager.h"
#include "../core/utils/logger.h"
#include "../core/models/monitor.h"
#include "../services/monitor_manager.h"

QmlMonitorManager::QmlMonitorManager(core::MonitorManager* coreManager, QObject* parent)
    : QObject(parent), m_coreManager(coreManager), m_selectedMonitor(nullptr)
{
    log(core::LogLevel::Info, "Initializing QmlMonitorManager...");
    rescan();
}

QList<QObject*> QmlMonitorManager::getMonitors() const {
    return m_monitors;
}

QObject* QmlMonitorManager::getSelectedMonitor() const {
    return m_selectedMonitor;
}

void QmlMonitorManager::rescan() {
    log(core::LogLevel::Info, "Rescanning monitors...");

    const auto coreMonitors = m_coreManager->getMonitors();
    m_monitors.clear();

    for (const auto& monitor : coreMonitors) {
        auto* qmlMonitor = new QmlMonitor(monitor);
        m_monitors.append(qmlMonitor);
    }

    m_selectedMonitor = m_monitors.isEmpty() ? nullptr : m_monitors.first();

    log(core::LogLevel::Debug, "Rescan found " + std::to_string(m_monitors.size()) + " monitor(s).");
    if (m_selectedMonitor) {
        auto* mon = qobject_cast<QmlMonitor*>(m_selectedMonitor);
        if (mon)
            log(core::LogLevel::Debug, "Selected monitor after rescan: " + mon->getName().toStdString());
    }

    emit monitorsChanged();
    emit selectedMonitorChanged();
}

void QmlMonitorManager::apply() {
    log(core::LogLevel::Info, "Applying monitor configuration...");

    std::vector<core::Monitor> coreMonitors;

    for (auto* obj : m_monitors) {
        auto* qmlMon = qobject_cast<QmlMonitor*>(obj);
        if (qmlMon)
            coreMonitors.push_back(qmlMon->internal());  // copies underlying core::Monitor
    }

    if (!m_coreManager->applyMonitorConfiguration(coreMonitors)) {
        log(core::LogLevel::Error, "Failed to apply monitor configuration.");
    } else {
        log(core::LogLevel::Info, "Monitor configuration applied successfully.");
    }
}


