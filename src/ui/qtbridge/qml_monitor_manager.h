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
    Q_PROPERTY(int selectedMonitorIndex_ READ getSelectedMonitorIndex WRITE setSelectedMonitorIndex
                   NOTIFY selectedMonitorIndexChanged)

   public:
    explicit QmlMonitorManager(core::HyprMonitorManager* coreManager, QObject* parent = nullptr);
    ~QmlMonitorManager();

    // core methods
    Q_INVOKABLE void scanMonitors();
    Q_INVOKABLE void applyMonitorConfiguration();
    Q_INVOKABLE void revertMonitorConfiguration();
    Q_INVOKABLE QPoint getSnappedPosition(const QString& monitorName);
    Q_INVOKABLE QPoint calculateOffsetToCenter(double scaleFactor, int width, int height);
    Q_INVOKABLE double calculatePreviewScaleFactor(int areaWidth, int areaHeight,
                                                   float marginPercentage);

    // accessors
    Q_INVOKABLE QmlMonitor* getSelectedMonitor() const;
    auto getMonitors() const -> QList<QmlMonitor*>;
    auto getSelectedMonitorIndex() const -> int;
    auto setSelectedMonitorIndex(int index) -> void;

   signals:
    void monitorConfigurationApplied();
    void monitorsChanged();
    void selectedMonitorIndexChanged();

   private:
    // helper methods
    void clearQmlMonitors();
    QList<QmlMonitor*> wrapCoreMonitors(std::vector<core::Monitor>& monitors);
    QmlMonitor* wrapCoreMonitor(core::Monitor& monitor);

    // attributes
    core::HyprMonitorManager* coreManager_;
    QList<QmlMonitor*> monitors_;
    int selectedMonitorIndex_ = -1;
};

}  // namespace qtbridge
