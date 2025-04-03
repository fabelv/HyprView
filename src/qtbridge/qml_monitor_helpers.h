#pragma once

#include <QObject>
#include <QList>
#include "../core/models/monitor.h"
#include "../core/utils/monitor_helpers.h"
#include "qml_monitor.h"

class QmlMonitorHelpers : public QObject {
    Q_OBJECT

public:
    explicit QmlMonitorHelpers(QObject* parent = nullptr) : QObject(parent) {}

    Q_INVOKABLE QList<QmlMonitor*> removeMonitorById(const QList<QmlMonitor*>& monitors, QmlMonitor* monitorToRemove);
};
