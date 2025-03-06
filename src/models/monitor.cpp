#include "monitor.h"
#include <sstream>

// Constructor implementation
Monitor::Monitor(int id, const std::string& name, const std::string& description, const std::string& make, 
                 const std::string& model, const std::string& serial, int width, int height, double refreshRate, 
                 int x, int y, double scale, int transform, bool focused, bool dpmsStatus, bool vrr, int solitary,
                 bool activelyTearing, const std::string& directScanoutTo, bool disabled, const std::string& current_format, 
                 const std::string& mirror_of, const std::vector<std::string>& available_modes)
    : id(id), name(name), description(description), make(make), model(model), serial(serial),
      width(width), height(height), refreshRate(refreshRate), position_x(x), position_y(y), scale(scale),
      transform(transform), focused(focused), dpms_status(dpmsStatus), vrr(vrr), solitary(solitary),
      activelyTearing(activelyTearing), directScanoutTo(directScanoutTo), disabled(disabled),
      current_format(current_format), mirror_of(mirror_of), available_modes(available_modes) {}

// Convert monitor details to a readable string
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
    for (const std::string& mode : available_modes) {
        oss << mode << " ";
    }
    return oss.str();
}

// Define JSON to Monitor object conversion
void from_json(const nlohmann::json& j, Monitor& m) {
    j.at("id").get_to(m.id);
    j.at("name").get_to(m.name);
    j.at("description").get_to(m.description);
    j.at("make").get_to(m.make);
    j.at("model").get_to(m.model);
    j.at("serial").get_to(m.serial);
    j.at("width").get_to(m.width);
    j.at("height").get_to(m.height);
    j.at("refreshRate").get_to(m.refreshRate);
    j.at("x").get_to(m.position_x);
    j.at("y").get_to(m.position_y);
    j.at("scale").get_to(m.scale);
    j.at("transform").get_to(m.transform);
    j.at("focused").get_to(m.focused);
    j.at("dpmsStatus").get_to(m.dpms_status);
    j.at("vrr").get_to(m.vrr);
    j.at("solitary").get_to(m.solitary);
    j.at("activelyTearing").get_to(m.activelyTearing);
    j.at("directScanoutTo").get_to(m.directScanoutTo);
    j.at("disabled").get_to(m.disabled);
    j.at("currentFormat").get_to(m.current_format);
    j.at("mirrorOf").get_to(m.mirror_of);
    j.at("availableModes").get_to(m.available_modes);
}

