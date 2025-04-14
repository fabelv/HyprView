#pragma once

#include <QList>
#include <QObject>
#include <QPoint>
#include <vector>

#include "../../managers/hypr_monitor_manager.h"
#include "qml_monitor.h"

namespace qtbridge {

class QmlMonitorManager : public QObject {
    Q_OBJECT

    // qml properties
    Q_PROPERTY(QList<QmlMonitor*> monitors_ READ getMonitors NOTIFY monitorsChanged)
    Q_PROPERTY(QmlMonitor* selectedMonitor_ READ getSelectedMonitor WRITE setSelectedMonitor NOTIFY selectedMonitorChanged)

   public:
    explicit QmlMonitorManager(core::HyprMonitorManager* coreManager, QObject* parent = nullptr);
    ~QmlMonitorManager();

    // core methods
    Q_INVOKABLE void scanMonitors();
    Q_INVOKABLE void applyMonitorConfiguration();
    Q_INVOKABLE void revertMonitorConfiguration();
    Q_INVOKABLE QPoint getSnappedPosition(const QString& monitorName, const int currentX, const int currentY);
    Q_INVOKABLE QPoint calculateOffsetToCenter(double scaleFactor, int width, int height);
    Q_INVOKABLE double calculatePreviewScaleFactor(int areaWidth, int areaHeight,
                                                   float marginPercentage);

    // accessors
    Q_INVOKABLE QList<QmlMonitor*> getMonitors();
    Q_INVOKABLE QmlMonitor* getSelectedMonitor();
    Q_INVOKABLE void setSelectedMonitor(QmlMonitor* monitor);

   signals:
    void monitorConfigurationApplied();
    void monitorsChanged();
    void selectedMonitorChanged();

   private:
    // helper methods
    void clearQmlMonitors();
    QList<QmlMonitor*> wrapCoreMonitors(std::vector<core::Monitor>& monitors);
    QmlMonitor* wrapCoreMonitor(core::Monitor& monitor);

    // attributes
    core::HyprMonitorManager* coreManager_;
    QList<QmlMonitor*> monitors_;
    QmlMonitor* selectedMonitor_;
};

}  // namespace qtbridge
