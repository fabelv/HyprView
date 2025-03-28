#pragma once

#include "monitor_manager.h"
#include "../utils/monitor_parser.h"

class HyprMonitorManager : public MonitorManager {
private:
    MonitorParser* parser;

public:
    HyprMonitorManager(MonitorParser* parser);
    Q_INVOKABLE QList<Monitor*> getMonitors() const override;
    Q_INVOKABLE bool applyMonitorConfiguration(const QList<QObject*>& monitors) override;
};

