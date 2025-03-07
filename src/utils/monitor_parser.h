#ifndef MONITOR_PARSER_H
#define MONITOR_PARSER_H

#include "../models/monitor.h"
#include <vector>
#include <string>

class MonitorParser {
public:
    virtual ~MonitorParser() = default;
    virtual std::vector<Monitor> parseMonitorsFromJson(const std::string& jsonString) const = 0;
};

#endif
