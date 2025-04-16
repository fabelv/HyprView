#include "qml_monitor_manager.h"

#include <strings.h>

#include <cmath>
#include <vector>

#include "hyprview_core/models/monitor.h"
#include "hyprview_core/utils/logger.h"
#include "hyprview_core/utils/monitor_geometry.h"
#include "qml_monitor.h"

namespace qtbridge {

QmlMonitorManager::QmlMonitorManager(core::HyprMonitorManager* coreManager, QObject* parent)
    : QObject(parent), coreManager_(coreManager) {
    log(core::LogLevel::Info, "Initializing QmlMonitorManager...");
    scanMonitors();
}

QmlMonitorManager::~QmlMonitorManager() { clearQmlMonitors(); }

void QmlMonitorManager::clearQmlMonitors() {
    selectedMonitor_ = nullptr;
    emit selectedMonitorChanged();

    qDeleteAll(monitors_);
    monitors_.clear();
    emit monitorsChanged();
}

QList<QmlMonitor*> QmlMonitorManager::wrapCoreMonitors(std::vector<core::Monitor>& monitors) {
    QList<QmlMonitor*> list;
    for (core::Monitor& mon : monitors) {
        list.append(wrapCoreMonitor(mon));
    }
    return list;
}

QmlMonitor* QmlMonitorManager::wrapCoreMonitor(core::Monitor& monitor) {
    return new QmlMonitor(&monitor, this);
}

void QmlMonitorManager::scanMonitors() {
    log(core::LogLevel::Info, "Scanning monitors...");
    coreManager_->scanMonitors();

    clearQmlMonitors();
    monitors_ = wrapCoreMonitors(coreManager_->getMonitors());
    selectedMonitor_ = nullptr;

    emit monitorsChanged();
    emit selectedMonitorChanged();
}

QPoint QmlMonitorManager::getSnappedPosition(const QString& monitorName, const int currentX,
                                             const int currentY) {
    const core::Monitor* dragged = selectedMonitor_->getMonitor();
    const auto& allMonitors = coreManager_->getMonitors();
    const auto pos =
        core::MonitorGeometry::getSnappedPosition(*dragged, allMonitors, currentX, currentY);
    return QPoint(pos.x, pos.y);
}

double QmlMonitorManager::calculatePreviewScaleFactor(int areaWidth, int areaHeight,
                                                      float marginPercentage) {
    return core::MonitorGeometry::calculatePreviewScaleFactor(
        areaWidth, areaHeight, marginPercentage, coreManager_->getMonitors());
}

QPoint QmlMonitorManager::calculateOffsetToCenter(double scaleFactor, int width, int height) {
    auto pos = core::MonitorGeometry::calculateCenteredOffset(coreManager_->getMonitors(),
                                                              scaleFactor, width, height);
    return QPoint(pos.x, pos.y);
}

void QmlMonitorManager::applyMonitorConfiguration() {
    coreManager_->applyMonitorConfiguration();
    emit monitorConfigurationApplied();
}

void QmlMonitorManager::revertMonitorConfiguration() {
    coreManager_->revertMonitorConfiguration();
    emit monitorsChanged();
}

QList<QmlMonitor*> QmlMonitorManager::getMonitors() { return monitors_; }

QmlMonitor* QmlMonitorManager::getSelectedMonitor() { return selectedMonitor_; }

void QmlMonitorManager::setSelectedMonitor(QmlMonitor* monitor) {
    if (!monitor || selectedMonitor_ == monitor) {
        core::log(core::LogLevel::Debug, "new selected monitor is already selected");
        return;
    }

    if (!monitors_.contains(monitor)) {
        core::log(core::LogLevel::Debug, "new selected monitor is not part of monitors");
        return;  // Optionally guard against invalid pointers
    }

    selectedMonitor_ = monitor;
    core::log(core::LogLevel::Debug,
              "new selected monitor: " + selectedMonitor_->getName().toStdString());
    emit selectedMonitorChanged();
}

}  // namespace qtbridge
