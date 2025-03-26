#pragma once

#include "../models/monitor.h"
#include <QList>
#include <QString>

class MonitorParser {
public:
    virtual ~MonitorParser() = default;
    virtual QList<Monitor*> parseMonitorsFromJson(const QString& jsonString) const = 0;
};

