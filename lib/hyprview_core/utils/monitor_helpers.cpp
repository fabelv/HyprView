#include "hyprview_core/utils/monitor_helpers.h"
#include "hyprview_core/models/monitor.h"
#include <string>
#include <vector>

namespace core {

std::vector<std::string> MonitorHelpers::getAvailableMirrorMonitors(const Monitor &selectedMonitor, const std::vector<Monitor> &monitors){
    std::vector<std::string> availableMirrorMonitors;

    if (selectedMonitor.getMirrorOf() == ""){
        availableMirrorMonitors.push_back("none");
    }

    for (const Monitor &m : monitors){
        if (m.getName() == selectedMonitor.getName()) continue;

        availableMirrorMonitors.push_back(m.getName());
    }

    if (selectedMonitor.getMirrorOf() != ""){
        availableMirrorMonitors.push_back("none");
    }

    return availableMirrorMonitors;
}

}
