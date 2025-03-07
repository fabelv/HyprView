#ifndef MONITOR_H
#define MONITOR_H

#include <string>
#include <vector>

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
        int positionX;
        int positionY;
        double scale;
        int transform;
        bool focused;
        bool dpmsStatus;
        bool vrr;
        int solitary;
        bool activelyTearing;
        std::string directScanoutTo;
        bool disabled;
        std::string currentFormat;
        std::string mirrorOf;
        std::vector<std::string> availableModes;

    public:
        Monitor();
        Monitor(int id, const std::string& name, const std::string& description,
                const std::string& make, const std::string& model, const std::string& serial,
                int width, int height, double refreshRate, int x, int y, double scale, int transform,
                bool focused, bool dpmsStatus, bool vrr, int solitary, bool activelyTearing,
                const std::string& directScanoutTo, bool disabled, const std::string& currentFormat,
                const std::string& mirrorOf, const std::vector<std::string>& availableModes);

        std::string toString() const;

        // Getters
        int getId() const { return id; }
        std::string getName() const { return name; }
        std::string getDescription() const { return description; }
        std::string getMake() const { return make; }
        std::string getModel() const { return model; }
        std::string getSerial() const { return serial; }
        int getWidth() const { return width; }
        int getHeight() const { return height; }
        double getRefreshRate() const { return refreshRate; }
        int getPositionX() const { return positionX; }
        int getPositionY() const { return positionY; }
        double getScale() const { return scale; }
        int getTransform() const { return transform; }
        bool isFocused() const { return focused; }
        bool getDpmsStatus() const { return dpmsStatus; }
        bool isVrrEnabled() const { return vrr; }
        int getSolitary() const { return solitary; }
        bool isActivelyTearing() const { return activelyTearing; }
        std::string getDirectScanoutTo() const { return directScanoutTo; }
        bool isDisabled() const { return disabled; }
        std::string getCurrentFormat() const { return currentFormat; }
        std::string getMirrorOf() const { return mirrorOf; }
        std::vector<std::string> getAvailableModes() const { return availableModes; }
};

#endif

