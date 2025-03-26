#include "monitor.h"

Monitor::Monitor(QObject* parent)
    : QObject(parent),
      id(0),
      width(0),
      height(0),
      refreshRate(0.0),
      positionX(0),
      positionY(0),
      scale(1.0),
      transform(0),
      focused(false),
      dpmsStatus(false),
      vrr(false),
      solitary("0"),
      activelyTearing(false),
      disabled(false)
{}

QString Monitor::toString() const {
    return QString("Monitor[%1] %2 (%3x%4 @ %5Hz)")
        .arg(id)
        .arg(name)
        .arg(width)
        .arg(height)
        .arg(refreshRate);
}

// Getters
int Monitor::getId() const { return id; }
QString Monitor::getName() const { return name; }
QString Monitor::getDescription() const { return description; }
QString Monitor::getMake() const { return make; }
QString Monitor::getModel() const { return model; }
QString Monitor::getSerial() const { return serial; }
int Monitor::getWidth() const { return width; }
int Monitor::getHeight() const { return height; }
double Monitor::getRefreshRate() const { return refreshRate; }
int Monitor::getPositionX() const { return positionX; }
int Monitor::getPositionY() const { return positionY; }
double Monitor::getScale() const { return scale; }
int Monitor::getTransform() const { return transform; }
bool Monitor::isFocused() const { return focused; }
bool Monitor::getDpmsStatus() const { return dpmsStatus; }
bool Monitor::isVrrEnabled() const { return vrr; }
QString Monitor::getSolitary() const { return solitary; }
bool Monitor::isActivelyTearing() const { return activelyTearing; }
QString Monitor::getDirectScanoutTo() const { return directScanoutTo; }
bool Monitor::isDisabled() const { return disabled; }
QString Monitor::getCurrentFormat() const { return currentFormat; }
QString Monitor::getMirrorOf() const { return mirrorOf; }
QStringList Monitor::getAvailableModes() const { return availableModes; }

// Setters
void Monitor::setId(int value) { if (id != value) { id = value; emit changed(); } }
void Monitor::setName(const QString& value) { if (name != value) { name = value; emit changed(); } }
void Monitor::setDescription(const QString& value) { if (description != value) { description = value; emit changed(); } }
void Monitor::setMake(const QString& value) { if (make != value) { make = value; emit changed(); } }
void Monitor::setModel(const QString& value) { if (model != value) { model = value; emit changed(); } }
void Monitor::setSerial(const QString& value) { if (serial != value) { serial = value; emit changed(); } }
void Monitor::setWidth(int value) { if (width != value) { width = value; emit changed(); } }
void Monitor::setHeight(int value) { if (height != value) { height = value; emit changed(); } }
void Monitor::setRefreshRate(double value) { if (!qFuzzyCompare(refreshRate, value)) { refreshRate = value; emit changed(); } }
void Monitor::setPositionX(int value) { if (positionX != value) { positionX = value; emit changed(); } }
void Monitor::setPositionY(int value) { if (positionY != value) { positionY = value; emit changed(); } }
void Monitor::setScale(double value) { if (!qFuzzyCompare(scale, value)) { scale = value; emit changed(); } }
void Monitor::setTransform(int value) { if (transform != value) { transform = value; emit changed(); } }
void Monitor::setFocused(bool value) { if (focused != value) { focused = value; emit changed(); } }
void Monitor::setDpmsStatus(bool value) { if (dpmsStatus != value) { dpmsStatus = value; emit changed(); } }
void Monitor::setVrrEnabled(bool value) { if (vrr != value) { vrr = value; emit changed(); } }
void Monitor::setSolitary(const QString& value) { if (solitary != value) { solitary = value; emit changed(); } }
void Monitor::setActivelyTearing(bool value) { if (activelyTearing != value) { activelyTearing = value; emit changed(); } }
void Monitor::setDirectScanoutTo(const QString& value) { if (directScanoutTo != value) { directScanoutTo = value; emit changed(); } }
void Monitor::setDisabled(bool value) { if (disabled != value) { disabled = value; emit changed(); } }
void Monitor::setCurrentFormat(const QString& value) { if (currentFormat != value) { currentFormat = value; emit changed(); } }
void Monitor::setMirrorOf(const QString& value) { if (mirrorOf != value) { mirrorOf = value; emit changed(); } }
void Monitor::setAvailableModes(const QStringList& value) { if (availableModes != value) { availableModes = value; emit changed(); } }
