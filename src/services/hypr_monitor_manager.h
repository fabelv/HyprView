#pragma once

#include "monitor_manager.h"
#include "../utils/monitor_parser.h"

class HyprMonitorManager : public MonitorManager {
private:
    MonitorParser* parser;

public:
    HyprMonitorManager(MonitorParser* parser);
    QList<Monitor*> getMonitors() const override;
    bool applyMonitorConfiguration(const QList<Monitor*>& monitors) override;
};

