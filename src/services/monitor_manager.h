#pragma once

#include "../models/monitor.h"
#include <QList>

class MonitorManager {
public:
    virtual ~MonitorManager() = default;

    virtual QList<Monitor*> getMonitors() const = 0;
    virtual bool applyMonitorConfiguration(const QList<Monitor*>& monitors) = 0;
};

