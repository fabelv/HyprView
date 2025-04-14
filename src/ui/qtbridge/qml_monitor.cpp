#include "qml_monitor.h"

#include <QDebug>
#include <QString>
#include <QStringList>
#include <string>

namespace qtbridge {

QmlMonitor::QmlMonitor(core::Monitor* monitor, QObject* parent)
    : QObject(parent), monitor_(monitor) {}

auto QmlMonitor::getMonitor() const -> const core::Monitor* { return monitor_; }

QString QmlMonitor::generateCurrentMode() const {
    return QString::fromStdString(monitor_->generateCurrentMode());
}

void QmlMonitor::applyModeString(const QString& mode) {
    monitor_->applyModeString(mode.toStdString());
    emit updated();
}

auto QmlMonitor::getId() const -> const int { 
    return monitor_->getId(); 
}

auto QmlMonitor::setId(int value) -> void {
    monitor_->setId(value);
    emit updated();
}

auto QmlMonitor::getName() const -> const QString {
    return QString::fromStdString(monitor_->getName());
}

auto QmlMonitor::setName(const QString& value) -> void {
    monitor_->setName(value.toStdString());
    emit updated();
}

auto QmlMonitor::getDescription() const -> const QString {
    return QString::fromStdString(monitor_->getDescription());
}

auto QmlMonitor::setDescription(const QString& value) -> void {
    monitor_->setDescription(value.toStdString());
    emit updated();
}

auto QmlMonitor::getMake() const -> const QString {
    return QString::fromStdString(monitor_->getMake());
}

auto QmlMonitor::setMake(const QString& value) -> void {
    monitor_->setMake(value.toStdString());
    emit updated();
}

auto QmlMonitor::getModel() const -> const QString {
    return QString::fromStdString(monitor_->getModel());
}

auto QmlMonitor::setModel(const QString& value) -> void {
    monitor_->setModel(value.toStdString());
    emit updated();
}

auto QmlMonitor::getSerial() const -> const QString {
    return QString::fromStdString(monitor_->getSerial());
}

auto QmlMonitor::setSerial(const QString& value) -> void {
    monitor_->setSerial(value.toStdString());
    emit updated();
}

auto QmlMonitor::getWidth() const -> const int { return monitor_->getWidth(); }

auto QmlMonitor::setWidth(int value) -> void {
    monitor_->setWidth(value);
    emit updated();
}

auto QmlMonitor::getHeight() const -> const int { return monitor_->getHeight(); }

auto QmlMonitor::setHeight(int value) -> void {
    monitor_->setHeight(value);
    emit updated();
}

auto QmlMonitor::getRefreshRate() const -> const double { return monitor_->getRefreshRate(); }

auto QmlMonitor::setRefreshRate(double value) -> void {
    monitor_->setRefreshRate(value);
    emit updated();
}

auto QmlMonitor::getPositionX() const -> const int { return monitor_->getPositionX(); }

auto QmlMonitor::setPositionX(int value) -> void {
    if (monitor_->getPositionX() != value) {
        monitor_->setPositionX(value);
        emit updated();
    }
}

auto QmlMonitor::getPositionY() const -> const int { return monitor_->getPositionY(); }

auto QmlMonitor::setPositionY(int value) -> void {
    if (monitor_->getPositionY() != value) {
        monitor_->setPositionY(value);
        emit updated();
    }
}

auto QmlMonitor::getScale() const -> const double { return monitor_->getScale(); }

auto QmlMonitor::setScale(double value) -> void {
    monitor_->setScale(value);
    emit updated();
}

auto QmlMonitor::getTransform() const -> const int {
    return static_cast<int>(monitor_->getTransform());
}

auto QmlMonitor::setTransform(int value) -> void {
    monitor_->setTransform(static_cast<core::Transform>(value));
    emit updated();
}

auto QmlMonitor::getDpmsStatus() const -> const bool { return monitor_->getDpmsStatus(); }

auto QmlMonitor::setDpmsStatus(bool value) -> void {
    monitor_->setDpmsStatus(value);
    emit updated();
}

auto QmlMonitor::getVrr() const -> const bool { return monitor_->getVrrEnabled(); }

auto QmlMonitor::setVrr(bool value) -> void {
    monitor_->setVrrEnabled(value);
    emit updated();
}

auto QmlMonitor::getSolitary() const -> const QString {
    return QString::fromStdString(monitor_->getSolitary());
}

auto QmlMonitor::setSolitary(const QString& value) -> void {
    monitor_->setSolitary(value.toStdString());
    emit updated();
}

auto QmlMonitor::getActivelyTearing() const -> const bool { return monitor_->getActivelyTearing(); }

auto QmlMonitor::setActivelyTearing(bool value) -> void {
    monitor_->setActivelyTearing(value);
    emit updated();
}

auto QmlMonitor::getDirectScanoutTo() const -> const QString {
    return QString::fromStdString(monitor_->getDirectScanoutTo());
}

auto QmlMonitor::setDirectScanoutTo(const QString& value) -> void {
    monitor_->setDirectScanoutTo(value.toStdString());
    emit updated();
}

auto QmlMonitor::getDisabled() const -> const bool { return monitor_->getDisabled(); }

auto QmlMonitor::setDisabled(bool value) -> void {
    monitor_->setDisabled(value);
    emit updated();
}

auto QmlMonitor::getCurrentFormat() const -> const QString {
    return QString::fromStdString(monitor_->getCurrentFormat());
}

auto QmlMonitor::setCurrentFormat(const QString& value) -> void {
    monitor_->setCurrentFormat(value.toStdString());
    emit updated();
}

auto QmlMonitor::getMirrorOf() const -> const QString {
    return QString::fromStdString(monitor_->getMirrorOf());
}

auto QmlMonitor::setMirrorOf(const QString& value) -> void {
    monitor_->setMirrorOf(value.toStdString());
    emit updated();
}

auto QmlMonitor::getAvailableModes() const -> const QStringList {
    QStringList list;
    for (const auto& s : monitor_->getAvailableModes()) {
        list.append(QString::fromStdString(s));
    }
    return list;
}

auto QmlMonitor::setAvailableModes(const QStringList& value) -> void {
    std::vector<std::string> vec;
    for (const auto& s : value) vec.push_back(s.toStdString());
    monitor_->setAvailableModes(vec);
    emit updated();
}

}  // namespace qtbridge
