#include "qml_monitor_manager.h"
#include "hyprview_core/models/monitor.h"
#include "hyprview_core/utils/logger.h"
#include "hyprview_core/utils/monitor_geometry.h"
#include "qml_monitor.h"
#include <vector>

QmlMonitorManager::QmlMonitorManager(core::HyprMonitorManager *coreManager,
                                     QObject *parent)
    : QObject(parent), m_coreManager(coreManager), m_selectedMonitor(nullptr) {
  log(core::LogLevel::Info, "Initializing QmlMonitorManager...");
  scanMonitors();
}

QmlMonitorManager::~QmlMonitorManager() { clearQmlMonitors(); }

void QmlMonitorManager::clearQmlMonitors() {
  m_selectedMonitor = nullptr;
  /*emit selectedMonitorChanged();*/

  qDeleteAll(m_monitors);
  m_monitors.clear();
  /*emit monitorsChanged();*/
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
  m_coreManager->scanMonitors();

  clearQmlMonitors();
  m_monitors = wrapCoreMonitors(m_coreManager->getMonitors());
  m_selectedMonitor = wrapCoreMonitor(m_coreManager->getSelectedMonitor());

  emit monitorsChanged();
  emit selectedMonitorChanged();
}

QList<QmlMonitor *> QmlMonitorManager::getMonitors() const {
  return m_monitors;
}

QmlMonitor *QmlMonitorManager::getSelectedMonitor() const {
  return m_selectedMonitor;
}

void QmlMonitorManager::setSelectedMonitor(QmlMonitor *monitor) {
  if (m_selectedMonitor != monitor) {
    m_selectedMonitor = monitor;
    emit selectedMonitorChanged();
  }
}

QPoint QmlMonitorManager::getSnappedPosition(const QString &monitorName) {
  const auto *dragged =
      m_coreManager->findMonitorByName(monitorName.toStdString());
  if (!dragged)
    return QPoint(0, 0);

  const auto &allMonitors = m_coreManager->getMonitors();
  const auto pos =
      core::MonitorGeometry::getSnappedPosition(*dragged, allMonitors);
  return QPoint(pos.x, pos.y);
}

double QmlMonitorManager::calculatePreviewScaleFactor(int areaWidth,
                                                      int areaHeight,
                                                      float marginPercentage) {
  return core::MonitorGeometry::calculatePreviewScaleFactor(
      areaWidth, areaHeight, marginPercentage, m_coreManager->getMonitors());
}

QPoint QmlMonitorManager::calculateOffsetToCenter(double scaleFactor, int width,
                                                  int height) {
  auto pos = core::MonitorGeometry::calculateCenteredOffset(
      m_coreManager->getMonitors(), scaleFactor, width, height);
  return QPoint(pos.x, pos.y);
}

void QmlMonitorManager::applyMonitorConfiguration() {
  m_coreManager->applyMonitorConfiguration();
  emit monitorConfigurationApplied();
}

void QmlMonitorManager::revertMonitorConfiguration() {
  m_coreManager->revertMonitorConfiguration();
  emit monitorsChanged();
}
