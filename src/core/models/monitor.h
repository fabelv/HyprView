#pragma once

#include <string>
#include <vector>
#include "enums/transform.h"

namespace core {

class Monitor {
public:
    Monitor();

    std::string toString() const;
    void applyModeString(const std::string& mode);
    std::string generateCurrentMode() const;

    // Getters
    int getId() const;
    const std::string& getName() const;
    const std::string& getDescription() const;
    const std::string& getMake() const;
    const std::string& getModel() const;
    const std::string& getSerial() const;
    int getWidth() const;
    int getHeight() const;
    double getRefreshRate() const;
    int getPositionX() const;
    int getPositionY() const;
    double getScale() const;
    Transform getTransform() const;
    bool isFocused() const;
    bool getDpmsStatus() const;
    bool isVrrEnabled() const;
    const std::string& getSolitary() const;
    bool isActivelyTearing() const;
    const std::string& getDirectScanoutTo() const;
    bool isDisabled() const;
    const std::string& getCurrentFormat() const;
    const std::string& getMirrorOf() const;
    const std::vector<std::string>& getAvailableModes() const;

    // Setters
    void setId(int);
    void setName(const std::string&);
    void setDescription(const std::string&);
    void setMake(const std::string&);
    void setModel(const std::string&);
    void setSerial(const std::string&);
    void setWidth(int);
    void setHeight(int);
    void setRefreshRate(double);
    void setPositionX(int);
    void setPositionY(int);
    void setScale(double);
    void setTransform(Transform);
    void setFocused(bool);
    void setDpmsStatus(bool);
    void setVrrEnabled(bool);
    void setSolitary(const std::string&);
    void setActivelyTearing(bool);
    void setDirectScanoutTo(const std::string&);
    void setDisabled(bool);
    void setCurrentFormat(const std::string&);
    void setMirrorOf(const std::string&);
    void setAvailableModes(const std::vector<std::string>&);

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
    int positionX;
    int positionY;
    double scale;
    Transform transform;
    bool focused;
    bool dpmsStatus;
    bool vrr;
    std::string solitary;
    bool activelyTearing;
    std::string directScanoutTo;
    bool disabled;
    std::string currentFormat;
    std::string mirrorOf;
    std::vector<std::string> availableModes;
};

} // namespace core
