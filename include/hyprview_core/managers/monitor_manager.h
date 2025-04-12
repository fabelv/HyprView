#pragma once

#include <memory>
#include <vector>

#include "hyprview_core/models/monitor.h"
#include "hyprview_core/parsers/monitor_parser.h"

namespace core {

class MonitorManager {
   public:
    // accessors
    auto getMonitors() -> std::vector<Monitor> &;

   protected:
    // constructors
    explicit MonitorManager(const std::shared_ptr<MonitorParser> &parser);
    virtual ~MonitorManager() = default;

    // core methods
    virtual auto scanMonitors() -> void = 0;
    virtual auto applyMonitorConfiguration() -> bool = 0;
    virtual auto revertMonitorConfiguration() -> bool = 0;

    // accessors
    auto setMonitors(std::vector<Monitor> &monitors) -> void;
    auto getPreUserEditMonitors() -> std::vector<Monitor> &;

    // attributes
    std::shared_ptr<MonitorParser> parser_;

   private:
    // attributes
    std::vector<Monitor> currentMonitors_;
    std::vector<Monitor> preUserEditMonitors_;
};

}  // namespace core
