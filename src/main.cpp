#include <iostream>
#include <vector>
#include <nlohmann/json.hpp>
#include "models/monitor.h"

using json = nlohmann::json;

// Function to execute hyprctl and capture the output
std::string runHyprctlCommand() {
    std::ostringstream output;
    FILE* pipe = popen("hyprctl monitors -j", "r");
    if (!pipe) {
        std::cerr << "Failed to run hyprctl command!" << std::endl;
        return "";
    }

    char buffer[128];
    while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
        output << buffer;
    }
    pclose(pipe);

    return output.str();
}

// Function to parse JSON and create Monitor objects directly
std::vector<Monitor> getMonitors() {
    std::vector<Monitor> monitors;
    std::string jsonString = runHyprctlCommand();

    if (jsonString.empty()) {
        std::cerr << "Error: Received empty JSON output from hyprctl." << std::endl;
        return monitors;
    }

    try {
        json jsonData = json::parse(jsonString);
        monitors = jsonData.get<std::vector<Monitor>>();  // Direct conversion
    } catch (const json::exception& e) {
        std::cerr << "JSON parsing error: " << e.what() << std::endl;
    }

    return monitors;
}

int main() {
    std::vector<Monitor> monitors = getMonitors();

    if (monitors.empty()) {
        std::cerr << "No monitor data found." << std::endl;
        return 1;
    }

    for (const auto& monitor : monitors) {
        std::cout << monitor.toString() << std::endl;
    }

    return 0;
}

