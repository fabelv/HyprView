#include "hypr_monitor_parser.h"
#include <nlohmann/json.hpp>
#include <iostream>

QList<Monitor*> HyprMonitorParser::parseMonitorsFromJson(const QString& jsonString) const {
    QList<Monitor*> monitors;

    try {
        auto json = nlohmann::json::parse(jsonString.toStdString());
        if (!json.is_array()) {
            std::cerr << "JSON is not an array!" << std::endl;
            return monitors;
        }

        for (const auto& obj : json) {
            auto* monitor = new Monitor();

            monitor->setId(obj["id"].get<int>());
            monitor->setName(QString::fromStdString(obj["name"].get<std::string>()));
            monitor->setDescription(QString::fromStdString(obj["description"].get<std::string>()));
            monitor->setMake(QString::fromStdString(obj["make"].get<std::string>()));
            monitor->setModel(QString::fromStdString(obj["model"].get<std::string>()));
            monitor->setSerial(QString::fromStdString(obj["serial"].get<std::string>()));
            monitor->setWidth(obj["width"].get<int>());
            monitor->setHeight(obj["height"].get<int>());
            monitor->setRefreshRate(obj["refreshRate"].get<double>());
            monitor->setPositionX(obj["x"].get<int>());
            monitor->setPositionY(obj["y"].get<int>());
            monitor->setScale(obj["scale"].get<double>());
            monitor->setTransform(obj["transform"].get<int>());
            monitor->setDpmsStatus(obj["dpmsStatus"].get<bool>());
            monitor->setVrrEnabled(obj["vrr"].get<bool>());

            monitor->setSolitary(QString::fromStdString(obj["solitary"].get<std::string>()));

            monitor->setActivelyTearing(obj["activelyTearing"].get<bool>());
            monitor->setDirectScanoutTo(QString::fromStdString(obj["directScanoutTo"].get<std::string>()));
            monitor->setDisabled(obj["disabled"].get<bool>());
            monitor->setCurrentFormat(QString::fromStdString(obj["currentFormat"].get<std::string>()));
            monitor->setMirrorOf(QString::fromStdString(obj["mirrorOf"].get<std::string>()));

            QStringList modes;
            for (const auto& mode : obj["availableModes"]) {
                modes.append(QString::fromStdString(mode.get<std::string>()));
            }
            monitor->setAvailableModes(modes);

            monitors.append(monitor);
        }

    } catch (const std::exception& e) {
        std::cerr << "Failed to parse monitor JSON: " << e.what() << std::endl;
    }

    return monitors;
}

