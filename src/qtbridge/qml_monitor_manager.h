#pragma once

#include <QObject>
#include <QList>
#include "../services/hypr_monitor_manager.h"
#include "qml_monitor.h"

class QmlMonitorManager : public QObject {
    Q_OBJECT

    Q_PROPERTY(QList<QmlMonitor*> monitors READ getMonitors NOTIFY monitorsChanged)
    Q_PROPERTY(QmlMonitor* selectedMonitor READ getSelectedMonitor WRITE setSelectedMonitor NOTIFY selectedMonitorChanged)

public:
    explicit QmlMonitorManager(core::HyprMonitorManager* coreManager, QObject* parent = nullptr);

    Q_INVOKABLE void applyMonitorConfiguration();
    Q_INVOKABLE void revertMonitorConfiguration();
    Q_INVOKABLE void scanMonitors();

    QList<QmlMonitor*> getMonitors() const;
    QmlMonitor* getSelectedMonitor() const;
    void setSelectedMonitor(QmlMonitor* monitor);

signals:
    void monitorConfigurationApplied();
    void monitorsChanged();
    void selectedMonitorChanged();

private:
    core::HyprMonitorManager* m_coreManager;
    QList<QmlMonitor*> m_monitors;
    QmlMonitor* m_selectedMonitor;
};

