#pragma once

#include <string>
#include <vector>

#include "hyprview_core/models/monitor.h"

namespace core {

class MonitorHelpers {
   public:
    static auto getAvailableMirrorMonitors(
        const Monitor &selectedMonitor, const std::vector<Monitor> &monitors) -> std::vector<std::string>;

    static auto getAvailableModes(const Monitor &monitor) -> std::vector<std::string>;

    static auto applyTransformation(Monitor& monitor, const Transform& transform) -> void;
};

}  // namespace core
