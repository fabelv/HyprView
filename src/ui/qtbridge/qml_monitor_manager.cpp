#include "qml_monitor_manager.h"
#include "hyprview_core/models/monitor.h"
#include "hyprview_core/utils/logger.h"
#include "hyprview_core/utils/monitor_geometry.h"
#include "qml_monitor.h"

#include <vector>

namespace qtbridge {

QmlMonitorManager::QmlMonitorManager(core::HyprMonitorManager *coreManager,
                                     QObject *parent)
    : QObject(parent), coreManager_(coreManager), selectedMonitorIndex_(-1) {
  log(core::LogLevel::Info, "Initializing QmlMonitorManager...");
  scanMonitors();
}

QmlMonitorManager::~QmlMonitorManager() { clearQmlMonitors(); }

void QmlMonitorManager::clearQmlMonitors() {
  selectedMonitorIndex_ = -1;
  emit selectedMonitorIndexChanged();

  qDeleteAll(monitors_);
  monitors_.clear();
  emit monitorsChanged();
}

QList<QmlMonitor *>
QmlMonitorManager::wrapCoreMonitors(std::vector<core::Monitor> &monitors) {
  QList<QmlMonitor *> list;
  for (core::Monitor &mon : monitors) {
    list.append(wrapCoreMonitor(mon));
  }
  return list;
}

QmlMonitor *QmlMonitorManager::wrapCoreMonitor(core::Monitor &monitor) {
  return new QmlMonitor(&monitor, this);
}

void QmlMonitorManager::scanMonitors() {
  log(core::LogLevel::Info, "Scanning monitors...");
  coreManager_->scanMonitors();

  clearQmlMonitors();
  monitors_ = wrapCoreMonitors(coreManager_->getMonitors());
  selectedMonitorIndex_ = 0;

  emit monitorsChanged();
  emit selectedMonitorIndexChanged();
}

QList<QmlMonitor *> QmlMonitorManager::getMonitors() const { return monitors_; }

QmlMonitor *QmlMonitorManager::getSelectedMonitor() const {
  if (selectedMonitorIndex_ >= 0 && selectedMonitorIndex_ < monitors_.size()) {
    return monitors_.at(selectedMonitorIndex_);
  }
  return nullptr;
}

int QmlMonitorManager::getSelectedMonitorIndex() const {
  return selectedMonitorIndex_;
}

void QmlMonitorManager::setSelectedMonitorIndex(int index) {
  if (index >= 0 && index < monitors_.size() &&
      index != selectedMonitorIndex_) {
    selectedMonitorIndex_ = index;
    emit selectedMonitorIndexChanged();
  }
}

QPoint QmlMonitorManager::getSnappedPosition(const QString &monitorName) {
  const auto &dragged =
      coreManager_->getMonitors().at(0); // TODO: adapt if needed
  const auto &allMonitors = coreManager_->getMonitors();
  const auto pos =
      core::MonitorGeometry::getSnappedPosition(dragged, allMonitors);
  return QPoint(pos.x, pos.y);
}

double QmlMonitorManager::calculatePreviewScaleFactor(int areaWidth,
                                                      int areaHeight,
                                                      float marginPercentage) {
  return core::MonitorGeometry::calculatePreviewScaleFactor(
      areaWidth, areaHeight, marginPercentage, coreManager_->getMonitors());
}

QPoint QmlMonitorManager::calculateOffsetToCenter(double scaleFactor, int width,
                                                  int height) {
  auto pos = core::MonitorGeometry::calculateCenteredOffset(
      coreManager_->getMonitors(), scaleFactor, width, height);
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

} // namespace qtbridge
