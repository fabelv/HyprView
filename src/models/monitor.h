#ifndef MONITOR_H
#define MONITOR_H

#include <string>
#include <vector>
#include <nlohmann/json.hpp>

class Monitor {
private:
    int id;
    std::string name;
    std::string description;
    std::string make;
    std::string model;
    std::string serial;
    int width;
    int height;
    double refreshRate;
    int position_x;
    int position_y;
    double scale;
    int transform;
    bool focused;
    bool dpms_status;
    bool vrr;
    int solitary;
    bool activelyTearing;
    std::string directScanoutTo;
    bool disabled;
    std::string current_format;
    std::string mirror_of;
    std::vector<std::string> available_modes;

public:
    // Default constructor
    Monitor() = default;

    // Constructor
    Monitor(int id, const std::string& name, const std::string& description, const std::string& make, 
            const std::string& model, const std::string& serial, int width, int height, double refreshRate, 
            int x, int y, double scale, int transform, bool focused, bool dpmsStatus, bool vrr, int solitary,
            bool activelyTearing, const std::string& directScanoutTo, bool disabled, const std::string& current_format, 
            const std::string& mirror_of, const std::vector<std::string>& available_modes);

    std::string toString() const;

    // Allow direct conversion from JSON
    friend void from_json(const nlohmann::json& j, Monitor& m);
};

#endif

