#include "hyprview_core/utils/monitor_helpers.h"

#include <stdexcept>
#include <string>
#include <vector>

#include "hyprview_core/enums/transform.h"
#include "hyprview_core/models/monitor.h"
#include "hyprview_core/utils/logger.h"

namespace core {

auto MonitorHelpers::getAvailableMirrorMonitors(const Monitor &selectedMonitor,
                                                const std::vector<Monitor> &monitors)
    -> std::vector<std::string> {
    if (monitors.empty()) {
        log(LogLevel::Error, "monitors must not be empty");
        throw std::invalid_argument("monitors must not be empty");
    }

    std::vector<std::string> availableMirrorMonitors;

    if (selectedMonitor.getMirrorOf() == "") {
        availableMirrorMonitors.emplace_back("none");
    }

    for (const Monitor &m : monitors) {
        if (m.getName() == selectedMonitor.getName()) continue;

        availableMirrorMonitors.emplace_back(m.getName());
    }

    if (selectedMonitor.getMirrorOf() != "") {
        availableMirrorMonitors.emplace_back("none");
    }

    return availableMirrorMonitors;
}

auto MonitorHelpers::getAvailableModes(const Monitor &monitor) -> std::vector<std::string> {
    auto availableModes = monitor.getAvailableModes();
    auto currentMode = monitor.generateCurrentMode();
    std::vector<std::string> modeOptions;

    // Always insert currentMode first
    modeOptions.push_back(currentMode);

    for (const std::string &mode : availableModes) {
        if (mode == currentMode) continue;
        modeOptions.push_back(mode);
    }

    return modeOptions;
}

auto MonitorHelpers::applyTransformation(Monitor &monitor, const Transform &transform) -> void {
    if (monitor.getTransform() == transform) return;

    auto oldHeight = monitor.getHeight();
    auto oldWidth = monitor.getWidth();

    auto isShapeSwapped = [](const Transform &t) {
        return t == Transform::Rotate90 || t == Transform::Rotate270 ||
               t == Transform::FlippedRotate90 || t == Transform::FlippedRotate270;
    };

    bool wasSwapped = isShapeSwapped(monitor.getTransform());
    bool nowSwapped = isShapeSwapped(transform);

    // Only update dimensions if we switch shape type (from normal to swapped or vice versa)
    if (wasSwapped != nowSwapped) {
        monitor.setHeight(oldWidth);
        monitor.setWidth(oldHeight);
    }
}

}  // namespace core
