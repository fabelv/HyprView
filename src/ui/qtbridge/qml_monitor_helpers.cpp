#include "qml_monitor_helpers.h"

#include <string>
#include <vector>

#include "hyprview_core/models/monitor.h"
#include "hyprview_core/utils/monitor_helpers.h"
#include "qml_monitor.h"

namespace qtbridge {

QList<QString> QmlMonitorHelpers::getAvailableMirrorMonitors(QmlMonitor* selectedQmlMonitor,
                                                             const QList<QObject*>& qmlMonitors) {
    if (!selectedQmlMonitor) return {};

    const core::Monitor selectedMonitor = *selectedQmlMonitor->getMonitor();
    std::vector<core::Monitor> monitors;

    for (QObject* obj : qmlMonitors) {
        auto* qmlMonitor = qobject_cast<QmlMonitor*>(obj);
        if (qmlMonitor && qmlMonitor->getMonitor()) {
            monitors.push_back(*qmlMonitor->getMonitor());
        }
    }

    auto availableMirrorMonitors =
        core::MonitorHelpers::getAvailableMirrorMonitors(selectedMonitor, monitors);

    QList<QString> result;
    result.reserve(static_cast<int>(availableMirrorMonitors.size()));
    for (const std::string& name : availableMirrorMonitors) {
        result.push_front(QString::fromStdString(name));
    }

    return result;
}

}  // namespace qtbridge
