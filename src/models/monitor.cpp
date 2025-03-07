#include "monitor.h"
#include <sstream>

Monitor::Monitor() {};
Monitor::Monitor(int id, const std::string& name, const std::string& description, const std::string& make, 
                 const std::string& model, const std::string& serial, int width, int height, double refreshRate, 
                 int x, int y, double scale, int transform, bool focused, bool dpmsStatus, bool vrr, int solitary,
                 bool activelyTearing, const std::string& directScanoutTo, bool disabled, const std::string& currentFormat, 
                 const std::string& mirrorOf, const std::vector<std::string>& availableModes)
    : id(id), name(name), description(description), make(make), model(model), serial(serial),
      width(width), height(height), refreshRate(refreshRate), positionX(x), positionY(y), scale(scale),
      transform(transform), focused(focused), dpmsStatus(dpmsStatus), vrr(vrr), solitary(solitary),
      activelyTearing(activelyTearing), directScanoutTo(directScanoutTo), disabled(disabled),
      currentFormat(currentFormat), mirrorOf(mirrorOf), availableModes(availableModes) {}

std::string Monitor::toString() const {
    std::ostringstream oss;
    oss << "Monitor: " << name << " (" << width << "x" << height << "@" << refreshRate << "Hz)" 
        << "\nDescription: " << description 
        << "\nMake: " << make 
        << "\nModel: " << model 
        << "\nSerial: " << serial 
        << "\nScale: " << scale 
        << "\nFocused: " << (focused ? "Yes" : "No") 
        << "\nDisabled: " << (disabled ? "Yes" : "No") 
        << "\nAvailable Modes: ";
    for (const std::string& mode : availableModes) {
        oss << mode << " ";
    }
    return oss.str();
}

