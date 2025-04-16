#pragma once

#include <string>
#include <vector>

#include "hyprview_core/enums/transform.h"

namespace core {

class Monitor {
   public:
    // constructors
    Monitor();
    Monitor(const Monitor& other) = default;

    // operators
    Monitor& operator=(const Monitor& other) = default;

    // core methods
    auto applyModeString(const std::string& mode)
        -> void;  // use mode format to set width, height and refreshRate
    auto generateCurrentMode() const
        -> std::string;  // modes format: <width>x<height>@<refreshRate>Hz
    auto toString() const -> std::string;

    // accessors
    auto getId() const -> const int;
    auto setId(int) -> void;

    auto getName() const -> const std::string&;
    auto setName(const std::string&) -> void;

    auto getDescription() const -> const std::string&;
    auto setDescription(const std::string&) -> void;

    auto getMake() const -> const std::string&;
    auto setMake(const std::string&) -> void;

    auto getModel() const -> const std::string&;
    auto setModel(const std::string&) -> void;

    auto getSerial() const -> const std::string&;
    auto setSerial(const std::string&) -> void;

    auto getWidth() const -> const int;
    auto setWidth(int) -> void;

    auto getHeight() const -> const int;
    auto setHeight(int) -> void;

    auto getRefreshRate() const -> const double;
    auto setRefreshRate(double) -> void;

    auto getPositionX() const -> const int;
    auto setPositionX(int) -> void;

    auto getPositionY() const -> const int;
    auto setPositionY(int) -> void;

    auto getScale() const -> const double;
    auto setScale(double) -> void;

    auto getTransform() const -> const Transform;
    auto setTransform(Transform) -> void;

    auto getDpmsStatus() const -> const bool;
    auto setDpmsStatus(bool) -> void;

    auto getVrrEnabled() const -> const bool;
    auto setVrrEnabled(bool) -> void;

    auto getSolitary() const -> const std::string&;
    auto setSolitary(const std::string&) -> void;

    auto getActivelyTearing() const -> const bool;
    auto setActivelyTearing(bool) -> void;

    auto getDirectScanoutTo() const -> const std::string&;
    auto setDirectScanoutTo(const std::string&) -> void;

    auto getDisabled() const -> const bool;
    auto setDisabled(bool) -> void;

    auto getCurrentFormat() const -> const std::string&;
    auto setCurrentFormat(const std::string&) -> void;

    auto getMirrorOf() const -> const std::string&;
    auto setMirrorOf(const std::string&) -> void;

    auto getAvailableModes() const -> const std::vector<std::string>&;
    auto setAvailableModes(const std::vector<std::string>&) -> void;

   private:
    // attributes
    int id_{};
    std::string name_{};
    std::string description_{};
    std::string make_{};
    std::string model_{};
    std::string serial_{};
    int width_{};
    int height_{};
    double refreshRate_{};
    int positionX_{};
    int positionY_{};
    double scale_{};
    Transform transform_{};
    bool dpmsStatus_{};
    bool vrr_{};
    std::string solitary_{};
    bool activelyTearing_{};
    std::string directScanoutTo_{};
    bool disabled_{};
    std::string currentFormat_{};
    std::string mirrorOf_{};
    std::vector<std::string> availableModes_{};  // modes format: <width>x<height>@<refreshRate>Hz
};

}  // namespace core
