#include "qml_monitor.h"
#include <QStringList>
#include <QString>
#include <QDebug>

QmlMonitor::QmlMonitor(core::Monitor monitor, QObject* parent)
    : QObject(parent), m_monitor(std::move(monitor)) {}

const core::Monitor& QmlMonitor::internal() const {
    return m_monitor;
}

QString QmlMonitor::generateCurrentMode() const {
    return QString::fromStdString(m_monitor.generateCurrentMode());
}

void QmlMonitor::applyModeString(const QString& mode) {
    m_monitor.applyModeString(mode.toStdString());
    emit updated();
}


int QmlMonitor::getId() const {
    return m_monitor.getId();
}

void QmlMonitor::setId(int value) {
    m_monitor.setId(value);
    emit updated();
}

QString QmlMonitor::getName() const {
    return QString::fromStdString(m_monitor.getName());
}

void QmlMonitor::setName(const QString& value) {
    m_monitor.setName(value.toStdString());
    emit updated();
}

QString QmlMonitor::getDescription() const {
    return QString::fromStdString(m_monitor.getDescription());
}

void QmlMonitor::setDescription(const QString& value) {
    m_monitor.setDescription(value.toStdString());
    emit updated();
}

QString QmlMonitor::getMake() const {
    return QString::fromStdString(m_monitor.getMake());
}

void QmlMonitor::setMake(const QString& value) {
    m_monitor.setMake(value.toStdString());
    emit updated();
}

QString QmlMonitor::getModel() const {
    return QString::fromStdString(m_monitor.getModel());
}

void QmlMonitor::setModel(const QString& value) {
    m_monitor.setModel(value.toStdString());
    emit updated();
}

QString QmlMonitor::getSerial() const {
    return QString::fromStdString(m_monitor.getSerial());
}

void QmlMonitor::setSerial(const QString& value) {
    m_monitor.setSerial(value.toStdString());
    emit updated();
}

int QmlMonitor::getWidth() const {
    return m_monitor.getWidth();
}

void QmlMonitor::setWidth(int value) {
    m_monitor.setWidth(value);
    emit updated();
}

int QmlMonitor::getHeight() const {
    return m_monitor.getHeight();
}

void QmlMonitor::setHeight(int value) {
    m_monitor.setHeight(value);
    emit updated();
}

double QmlMonitor::getRefreshRate() const {
    return m_monitor.getRefreshRate();
}

void QmlMonitor::setRefreshRate(double value) {
    m_monitor.setRefreshRate(value);
    emit updated();
}

int QmlMonitor::getPositionX() const {
    return m_monitor.getPositionX();
}

void QmlMonitor::setPositionX(int value) {
    if (m_monitor.getPositionX() != value) {
        m_monitor.setPositionX(value);
        emit updated();
    }
}

int QmlMonitor::getPositionY() const {
    return m_monitor.getPositionY();
}

void QmlMonitor::setPositionY(int value) {
    if (m_monitor.getPositionY() != value) {
        m_monitor.setPositionY(value);
        emit updated();
    }
}

double QmlMonitor::getScale() const {
    return m_monitor.getScale();
}

void QmlMonitor::setScale(double value) {
    m_monitor.setScale(value);
    emit updated();
}

int QmlMonitor::getTransform() const {
    return static_cast<int>(m_monitor.getTransform());
}

void QmlMonitor::setTransform(int value) {
    m_monitor.setTransform(static_cast<core::Transform>(value));
    emit updated();
}

bool QmlMonitor::getFocused() const {
    return m_monitor.isFocused();
}

void QmlMonitor::setFocused(bool value) {
    m_monitor.setFocused(value);
    emit updated();
}

bool QmlMonitor::getDpmsStatus() const {
    return m_monitor.getDpmsStatus();
}

void QmlMonitor::setDpmsStatus(bool value) {
    m_monitor.setDpmsStatus(value);
    emit updated();
}

bool QmlMonitor::getVrr() const {
    return m_monitor.isVrrEnabled();
}

void QmlMonitor::setVrr(bool value) {
    m_monitor.setVrrEnabled(value);
    emit updated();
}

QString QmlMonitor::getSolitary() const {
    return QString::fromStdString(m_monitor.getSolitary());
}

void QmlMonitor::setSolitary(const QString& value) {
    m_monitor.setSolitary(value.toStdString());
    emit updated();
}

bool QmlMonitor::getActivelyTearing() const {
    return m_monitor.isActivelyTearing();
}

void QmlMonitor::setActivelyTearing(bool value) {
    m_monitor.setActivelyTearing(value);
    emit updated();
}

QString QmlMonitor::getDirectScanoutTo() const {
    return QString::fromStdString(m_monitor.getDirectScanoutTo());
}

void QmlMonitor::setDirectScanoutTo(const QString& value) {
    m_monitor.setDirectScanoutTo(value.toStdString());
    emit updated();
}

bool QmlMonitor::isDisabled() const {
    return m_monitor.isDisabled();
}

void QmlMonitor::setDisabled(bool value) {
    m_monitor.setDisabled(value);
    emit updated();
}

QString QmlMonitor::getCurrentFormat() const {
    return QString::fromStdString(m_monitor.getCurrentFormat());
}

void QmlMonitor::setCurrentFormat(const QString& value) {
    m_monitor.setCurrentFormat(value.toStdString());
    emit updated();
}

QString QmlMonitor::getMirrorOf() const {
    return QString::fromStdString(m_monitor.getMirrorOf());
}

void QmlMonitor::setMirrorOf(const QString& value) {
    m_monitor.setMirrorOf(value.toStdString());
    emit updated();
}

QStringList QmlMonitor::getAvailableModes() const {
    QStringList list;
    for (const auto& s : m_monitor.getAvailableModes()) {
        list.append(QString::fromStdString(s));
    }
    return list;
}

void QmlMonitor::setAvailableModes(const QStringList& value) {
    std::vector<std::string> vec;
    for (const auto& s : value)
        vec.push_back(s.toStdString());
    m_monitor.setAvailableModes(vec);
    emit updated();
}

