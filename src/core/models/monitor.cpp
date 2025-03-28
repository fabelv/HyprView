#include "monitor.h"
#include "../utils/logger.h"
#include <regex>
#include <sstream>
#include <iostream>

namespace core {

Monitor::Monitor() {}

std::string Monitor::toString() const {
    std::ostringstream oss;
    oss << "Monitor[" << id << "] " << name
        << " (" << width << "x" << height << " @ " << refreshRate << "Hz)";
    return oss.str();
}

std::string Monitor::generateCurrentMode() const {
    std::ostringstream oss;
    oss << width << "x" << height << "@" << refreshRate << "Hz";
    std::string mode = oss.str();
    log(LogLevel::Debug, "Generated current mode: " + mode);
    return mode;
}

void Monitor::applyModeString(const std::string& mode) {
    std::regex re(R"((\d+)x(\d+)@([\d.]+)Hz)");
    std::smatch match;
    if (std::regex_match(mode, match, re)) {
        width = std::stoi(match[1]);
        height = std::stoi(match[2]);
        refreshRate = std::stod(match[3]);
        log(LogLevel::Debug, "Applied mode string: " + mode);
    } else {
        log(LogLevel::Error, "Invalid mode string: " + mode);
    }
}

// --- Getters ---
int Monitor::getId() const { return id; }
const std::string& Monitor::getName() const { return name; }
const std::string& Monitor::getDescription() const { return description; }
const std::string& Monitor::getMake() const { return make; }
const std::string& Monitor::getModel() const { return model; }
const std::string& Monitor::getSerial() const { return serial; }
int Monitor::getWidth() const { return width; }
int Monitor::getHeight() const { return height; }
double Monitor::getRefreshRate() const { return refreshRate; }
int Monitor::getPositionX() const { return positionX; }
int Monitor::getPositionY() const { return positionY; }
double Monitor::getScale() const { return scale; }
Transform Monitor::getTransform() const { return transform; }
bool Monitor::isFocused() const { return focused; }
bool Monitor::getDpmsStatus() const { return dpmsStatus; }
bool Monitor::isVrrEnabled() const { return vrr; }
const std::string& Monitor::getSolitary() const { return solitary; }
bool Monitor::isActivelyTearing() const { return activelyTearing; }
const std::string& Monitor::getDirectScanoutTo() const { return directScanoutTo; }
bool Monitor::isDisabled() const { return disabled; }
const std::string& Monitor::getCurrentFormat() const { return currentFormat; }
const std::string& Monitor::getMirrorOf() const { return mirrorOf; }
const std::vector<std::string>& Monitor::getAvailableModes() const { return availableModes; }

// --- Setters ---
void Monitor::setId(int value) { id = value; }
void Monitor::setName(const std::string& value) { name = value; }
void Monitor::setDescription(const std::string& value) { description = value; }
void Monitor::setMake(const std::string& value) { make = value; }
void Monitor::setModel(const std::string& value) { model = value; }
void Monitor::setSerial(const std::string& value) { serial = value; }
void Monitor::setWidth(int value) { width = value; }
void Monitor::setHeight(int value) { height = value; }
void Monitor::setRefreshRate(double value) { refreshRate = value; }
void Monitor::setPositionX(int value) { positionX = value; }
void Monitor::setPositionY(int value) { positionY = value; }
void Monitor::setScale(double value) { scale = value; }
void Monitor::setTransform(Transform value) { transform = value; }
void Monitor::setFocused(bool value) { focused = value; }
void Monitor::setDpmsStatus(bool value) { dpmsStatus = value; }
void Monitor::setVrrEnabled(bool value) { vrr = value; }
void Monitor::setSolitary(const std::string& value) { solitary = value; }
void Monitor::setActivelyTearing(bool value) { activelyTearing = value; }
void Monitor::setDirectScanoutTo(const std::string& value) { directScanoutTo = value; }
void Monitor::setDisabled(bool value) { disabled = value; }
void Monitor::setCurrentFormat(const std::string& value) { currentFormat = value; }
void Monitor::setMirrorOf(const std::string& value) { mirrorOf = value; }
void Monitor::setAvailableModes(const std::vector<std::string>& value) { availableModes = value; }

} // namespace core

