#include "hyprview_core/parsers/hypr_monitor_parser.h"
#include "hyprview_core/utils/logger.h"
#include <nlohmann/json.hpp>
#include <cmath>

namespace core {

    auto HyprMonitorParser::parseMonitorsFromJson(const std::string& jsonString) -> std::vector<Monitor> {
        std::vector<Monitor> monitors;

        try {
            auto json = nlohmann::json::parse(jsonString);

            if (!json.is_array()) {
                log(LogLevel::Error, "JSON is not an array");
                return monitors;
            }

            for (const auto& obj : json) {
                auto monitor = parseSingleMonitor(obj);
                if (monitor.has_value()) {
                    monitors.push_back(monitor.value());
                }
            }

        } catch (const std::exception& e) {
            log(LogLevel::Error, std::string("Failed to parse monitor JSON: ") + e.what());
        }

        return monitors;
    }

    auto HyprMonitorParser::parseSingleMonitor(const nlohmann::json& obj) -> std::optional<Monitor> {
        try {
            Monitor monitor;

            monitor.setId(obj.at("id").get<int>());
            monitor.setName(obj.at("name").get<std::string>());
            monitor.setDescription(obj.at("description").get<std::string>());
            monitor.setMake(obj.at("make").get<std::string>());
            monitor.setModel(obj.at("model").get<std::string>());
            monitor.setSerial(obj.at("serial").get<std::string>());
            monitor.setWidth(obj.at("width").get<int>());
            monitor.setHeight(obj.at("height").get<int>());
            monitor.setRefreshRate(std::round(obj.at("refreshRate").get<double>() * 100.0) / 100.0);
            monitor.setPositionX(obj.at("x").get<int>());
            monitor.setPositionY(obj.at("y").get<int>());
            monitor.setScale(obj.at("scale").get<double>());
            monitor.setTransform(static_cast<Transform>(obj.at("transform").get<int>()));
            monitor.setDpmsStatus(obj.at("dpmsStatus").get<bool>());
            monitor.setVrrEnabled(obj.at("vrr").get<bool>());
            monitor.setSolitary(obj.at("solitary").get<std::string>());
            monitor.setActivelyTearing(obj.at("activelyTearing").get<bool>());
            monitor.setDirectScanoutTo(obj.at("directScanoutTo").get<std::string>());
            monitor.setDisabled(obj.at("disabled").get<bool>());
            monitor.setCurrentFormat(obj.at("currentFormat").get<std::string>());
            monitor.setMirrorOf(obj.at("mirrorOf").get<std::string>());

            std::vector<std::string> modes;
            for (const auto& mode : obj.at("availableModes")) {
                modes.push_back(mode.get<std::string>());
            }
            monitor.setAvailableModes(modes);

            return monitor;

        } catch (const std::exception& e) {
            log(LogLevel::Error, std::string("Failed to parse monitor object: ") + e.what());
            return std::nullopt;
        }
    }

} // namespace core

