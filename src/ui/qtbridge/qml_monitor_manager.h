#pragma once

#include <QObject>
#include <QList>
#include <QPoint>
#include <vector>
#include "qml_monitor.h"
#include "../../managers/hypr_monitor_manager.h"

class QmlMonitorManager : public QObject {
    Q_OBJECT

    Q_PROPERTY(QList<QmlMonitor*> monitors READ getMonitors NOTIFY monitorsChanged)
    Q_PROPERTY(QmlMonitor* selectedMonitor READ getSelectedMonitor WRITE setSelectedMonitor NOTIFY selectedMonitorChanged)

public:
    explicit QmlMonitorManager(core::HyprMonitorManager* coreManager, QObject* parent = nullptr);
    ~QmlMonitorManager();

    Q_INVOKABLE void applyMonitorConfiguration();
    Q_INVOKABLE void revertMonitorConfiguration();
    Q_INVOKABLE void scanMonitors();
    Q_INVOKABLE QPoint getSnappedPosition(const QString &monitorName);
    Q_INVOKABLE QPoint calculateOffsetToCenter(double scaleFactor, int width, int height);
    Q_INVOKABLE double calculatePreviewScaleFactor(int areaWidth, int areaHeight, float marginPercentage);

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

    void clearQmlMonitors();
    QList<QmlMonitor*> wrapCoreMonitors(std::vector<core::Monitor> &monitors);
    QmlMonitor* wrapCoreMonitor(core::Monitor &monitor);
};
