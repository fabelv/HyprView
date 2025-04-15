#include <hyprview_core/models/monitor.h>
#include <hyprview_core/utils/logger.h>

#include <iostream>
#include <regex>
#include <sstream>
#include <string>

#include "hyprview_core/enums/transform.h"
#include "hyprview_core/utils/monitor_helpers.h"

namespace core {

Monitor::Monitor() {}

auto Monitor::generateCurrentMode() const -> std::string {
    std::ostringstream oss;
    oss << width_ << "x" << height_ << "@" << refreshRate_ << "Hz";
    std::string mode = oss.str();
    log(LogLevel::Debug, "Generated current mode: " + mode);
    return mode;
}

auto Monitor::applyModeString(const std::string& mode) -> void {
    std::regex re(R"((\d+)x(\d+)@([\d.]+)Hz)");
    std::smatch match;
    if (std::regex_match(mode, match, re)) {
        width_ = std::stoi(match[1]);
        height_ = std::stoi(match[2]);
        refreshRate_ = std::stod(match[3]);
        log(LogLevel::Debug, "Applied mode string: " + mode);
    } else {
        log(LogLevel::Error, "Invalid mode string: " + mode);
    }

    log(LogLevel::Debug, toString());
}

auto Monitor::toString() const -> std::string {
    std::ostringstream oss;

    oss << "Monitor {\n"
        << "  ID: " << id_ << ", " << "  Name: " << name_ << "\n"
        << "  Description: " << description_ << "\n"
        << "  Make: " << make_ << ", " << "  Model: " << model_ << "\n"
        << "  Serial: " << serial_ << "\n"
        << "  Width: " << width_ << ", " << "  Height: " << height_ << ", "
        << "  Refresh Rate: " << refreshRate_ << "\n"
        << "  Position X: " << positionX_ << ", " << "  Position Y: " << positionY_ << ", "
        << "  Scale: " << scale_ << "\n"
        << "  Transform: " << transform_ << "\n"
        << "  DPMS Status: " << dpmsStatus_ << ", " << "  VRR: " << vrr_ << ", "
        << "  Solitary: " << solitary_ << ", " << "  Actively Tearing: " << activelyTearing_ << "\n"
        << "  Direct Scanout To: " << directScanoutTo_ << ", " << "  Disabled: " << disabled_
        << "\n"
        << "  Current Format: " << currentFormat_ << ", " << "  Mirror Of: " << mirrorOf_ << "\n"
        << "  Available Modes: [";

    for (size_t i = 0; i < availableModes_.size(); ++i) {
        oss << availableModes_[i];
        if (i != availableModes_.size() - 1) oss << ", ";
    }

    oss << "]\n}";

    return oss.str();
}

auto Monitor::getId() const -> const int { return id_; }

auto Monitor::setId(int value) -> void {
    id_ = value;
}

auto Monitor::getName() const -> const std::string& { return name_; }

auto Monitor::setName(const std::string& value) -> void {
    name_ = value;
}

auto Monitor::getDescription() const -> const std::string& { return description_; }

auto Monitor::setDescription(const std::string& value) -> void {
    description_ = value;
}

auto Monitor::getMake() const -> const std::string& { return make_; }

auto Monitor::setMake(const std::string& value) -> void {
    make_ = value;
}

auto Monitor::getModel() const -> const std::string& { return model_; }

auto Monitor::setModel(const std::string& value) -> void {
    model_ = value;
}

auto Monitor::getSerial() const -> const std::string& { return serial_; }

auto Monitor::setSerial(const std::string& value) -> void {
    serial_ = value;
}

auto Monitor::getWidth() const -> const int { return width_; }

auto Monitor::setWidth(int value) -> void {
    width_ = value;
}

auto Monitor::getHeight() const -> const int { return height_; }

auto Monitor::setHeight(int value) -> void {
    height_ = value;
}

auto Monitor::getRefreshRate() const -> const double { return refreshRate_; }

auto Monitor::setRefreshRate(double value) -> void {
    refreshRate_ = value;
}

auto Monitor::getPositionX() const -> const int { return positionX_; }

auto Monitor::setPositionX(int value) -> void {
    positionX_ = value;
}

auto Monitor::getPositionY() const -> const int { return positionY_; }

auto Monitor::setPositionY(int value) -> void {
    positionY_ = value;
}

auto Monitor::getScale() const -> const double { return scale_; }

auto Monitor::setScale(double value) -> void {
    scale_ = value;
}

auto Monitor::getTransform() const -> const Transform { return transform_; }

auto Monitor::setTransform(Transform value) -> void {
    MonitorHelpers::applyTransformation(*this, value);

    transform_ = value;

}

auto Monitor::getDpmsStatus() const -> const bool { return dpmsStatus_; }

auto Monitor::setDpmsStatus(bool value) -> void {
    dpmsStatus_ = value;
}

auto Monitor::getVrrEnabled() const -> const bool { return vrr_; }

auto Monitor::setVrrEnabled(bool value) -> void {
    vrr_ = value;
}

auto Monitor::getSolitary() const -> const std::string& { return solitary_; }

auto Monitor::setSolitary(const std::string& value) -> void {
    solitary_ = value;
}

auto Monitor::getActivelyTearing() const -> const bool { return activelyTearing_; }

auto Monitor::setActivelyTearing(bool value) -> void {
    activelyTearing_ = value;
}

auto Monitor::getDirectScanoutTo() const -> const std::string& { return directScanoutTo_; }

auto Monitor::setDirectScanoutTo(const std::string& value) -> void {
    directScanoutTo_ = value;
}

auto Monitor::getDisabled() const -> const bool { return disabled_; }

auto Monitor::setDisabled(bool value) -> void {
    disabled_ = value;
}

auto Monitor::getCurrentFormat() const -> const std::string& { return currentFormat_; }

auto Monitor::setCurrentFormat(const std::string& value) -> void {
    currentFormat_ = value;
}

auto Monitor::getMirrorOf() const -> const std::string& { return mirrorOf_; }

auto Monitor::setMirrorOf(const std::string& value) -> void {
    mirrorOf_ = value;
}

auto Monitor::getAvailableModes() const -> const std::vector<std::string>& {
    return availableModes_;
}

auto Monitor::setAvailableModes(const std::vector<std::string>& value) -> void {
    availableModes_ = value;
}

}  // namespace core
