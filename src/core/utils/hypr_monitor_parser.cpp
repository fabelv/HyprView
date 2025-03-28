#include "hypr_monitor_parser.h"
#include "logger.h"
#include "../models/enums/transform.h"
#include <nlohmann/json.hpp>
#include <cmath>
#include <iostream>

namespace core {

std::vector<Monitor> HyprMonitorParser::parseMonitorsFromJson(const std::string& jsonString) const {
    std::vector<Monitor> monitors;

    try {
        auto json = nlohmann::json::parse(jsonString);
        if (!json.is_array()) {
            std::cerr << "JSON is not an array!" << std::endl;
            return monitors;
        }

        for (const auto& obj : json) {
            Monitor monitor;

            monitor.setId(obj["id"].get<int>());
            monitor.setName(obj["name"]);
            monitor.setDescription(obj["description"]);
            monitor.setMake(obj["make"]);
            monitor.setModel(obj["model"]);
            monitor.setSerial(obj["serial"]);
            monitor.setWidth(obj["width"].get<int>());
            monitor.setHeight(obj["height"].get<int>());
            monitor.setRefreshRate(std::round(obj["refreshRate"].get<double>() * 100.0) / 100.0);
            monitor.setPositionX(obj["x"].get<int>());
            monitor.setPositionY(obj["y"].get<int>());
            monitor.setScale(obj["scale"].get<double>());
            monitor.setTransform(static_cast<Transform>(obj["transform"].get<int>()));
            monitor.setDpmsStatus(obj["dpmsStatus"].get<bool>());
            monitor.setVrrEnabled(obj["vrr"].get<bool>());
            monitor.setSolitary(obj["solitary"]);
            monitor.setActivelyTearing(obj["activelyTearing"].get<bool>());
            monitor.setDirectScanoutTo(obj["directScanoutTo"]);
            monitor.setDisabled(obj["disabled"].get<bool>());
            monitor.setCurrentFormat(obj["currentFormat"]);
            monitor.setMirrorOf(obj["mirrorOf"]);

            std::vector<std::string> modes;
            for (const auto& mode : obj["availableModes"]) {
                modes.push_back(mode);
            }
            monitor.setAvailableModes(modes);

            monitors.push_back(monitor);
        }

    } catch (const std::exception& e) {
        log(LogLevel::Error, std::string("Failed to parse monitor JSON: ") + e.what());
    }

    return monitors;
}

} // namespace core

