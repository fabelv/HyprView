#ifndef HYPR_MONITOR_PARSER_H
#define HYPR_MONITOR_PARSER_H

#include "monitor_parser.h"
#include <nlohmann/json.hpp>

class HyprMonitorParser : public MonitorParser {
public:
    std::vector<Monitor> parseMonitorsFromJson(const std::string& jsonString) const override;
};

#endif

