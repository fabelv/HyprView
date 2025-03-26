#pragma once

#include "monitor_parser.h"

class HyprMonitorParser : public MonitorParser {
public:
    QList<Monitor*> parseMonitorsFromJson(const QString& jsonString) const override;
};

