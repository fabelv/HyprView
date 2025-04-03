#include "qml_monitor_helpers.h"

QList<QmlMonitor*> QmlMonitorHelpers::removeMonitorById(const QList<QmlMonitor*>& monitors, QmlMonitor* monitorToRemove) {
    std::vector<core::Monitor> coreMonitors;
    for (QmlMonitor* qm : monitors) {
        if (qm)
            coreMonitors.push_back(qm->internal());
    }

    std::vector<core::Monitor> filtered = core::MonitorHelpers::removeMonitorByName(coreMonitors, monitorToRemove->internal());

    QList<QmlMonitor*> result;
    for (const auto& cm : filtered) {
        result.append(new QmlMonitor(cm));
    }

    return result;
}
