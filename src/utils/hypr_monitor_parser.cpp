#include "hypr_monitor_parser.h"
#include <iostream>

std::vector<Monitor> HyprMonitorParser::parseMonitorsFromJson(const std::string& jsonString) const {
    std::vector<Monitor> monitors;
    
    try {
        auto json = nlohmann::json::parse(jsonString);
        if (!json.is_array()) {
            std::cerr << "JSON is not an array!" << std::endl;
            return monitors;
        }

        for (const auto& obj : json) {
            std::vector<std::string> availableModes;
            for (const auto& mode : obj["availableModes"]) {
                availableModes.push_back(mode.get<std::string>());
            }

            monitors.emplace_back(
                obj["id"].is_number() ? obj["id"].get<int>() : std::stoi(obj["id"].get<std::string>()),
                obj["name"].get<std::string>(),
                obj["description"].get<std::string>(),
                obj["make"].get<std::string>(),
                obj["model"].get<std::string>(),
                obj["serial"].get<std::string>(),
                obj["width"].is_number() ? obj["width"].get<int>() : std::stoi(obj["width"].get<std::string>()),
                obj["height"].is_number() ? obj["height"].get<int>() : std::stoi(obj["height"].get<std::string>()),
                obj["refreshRate"].is_number() ? obj["refreshRate"].get<double>() : std::stod(obj["refreshRate"].get<std::string>()),
                obj["x"].is_number() ? obj["x"].get<int>() : std::stoi(obj["x"].get<std::string>()),
                obj["y"].is_number() ? obj["y"].get<int>() : std::stoi(obj["y"].get<std::string>()),
                obj["scale"].is_number() ? obj["scale"].get<double>() : std::stod(obj["scale"].get<std::string>()),
                obj["transform"].is_number() ? obj["transform"].get<int>() : std::stoi(obj["transform"].get<std::string>()),
                obj["focused"].get<bool>(),
                obj["dpmsStatus"].get<bool>(),
                obj["vrr"].get<bool>(),
                obj["solitary"].is_number() ? obj["solitary"].get<int>() : std::stoi(obj["solitary"].get<std::string>()),
                obj["activelyTearing"].get<bool>(),
                obj["directScanoutTo"].get<std::string>(),
                obj["disabled"].get<bool>(),
                obj["currentFormat"].get<std::string>(),
                obj["mirrorOf"].get<std::string>(),
                availableModes
            );
        }
    } catch (const std::exception& e) {
        std::cerr << "Error parsing JSON: " << e.what() << std::endl;
    }

    return monitors;
}

