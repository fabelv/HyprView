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

// --- Getters ---
#define GETTER(type, name, func) \
    type QmlMonitor::get##name() const { return func; }

GETTER(int, Id, m_monitor.getId())
GETTER(QString, Name, QString::fromStdString(m_monitor.getName()))
GETTER(QString, Description, QString::fromStdString(m_monitor.getDescription()))
GETTER(QString, Make, QString::fromStdString(m_monitor.getMake()))
GETTER(QString, Model, QString::fromStdString(m_monitor.getModel()))
GETTER(QString, Serial, QString::fromStdString(m_monitor.getSerial()))
GETTER(int, Width, m_monitor.getWidth())
GETTER(int, Height, m_monitor.getHeight())
GETTER(double, RefreshRate, m_monitor.getRefreshRate())
GETTER(int, PositionX, m_monitor.getPositionX())
GETTER(int, PositionY, m_monitor.getPositionY())
GETTER(double, Scale, m_monitor.getScale())
GETTER(int, Transform, static_cast<int>(m_monitor.getTransform()))
GETTER(bool, Focused, m_monitor.isFocused())
GETTER(bool, DpmsStatus, m_monitor.getDpmsStatus())
GETTER(bool, Vrr, m_monitor.isVrrEnabled())
GETTER(QString, Solitary, QString::fromStdString(m_monitor.getSolitary()))
GETTER(bool, ActivelyTearing, m_monitor.isActivelyTearing())
GETTER(QString, DirectScanoutTo, QString::fromStdString(m_monitor.getDirectScanoutTo()))
GETTER(bool, Disabled, m_monitor.isDisabled())
GETTER(QString, CurrentFormat, QString::fromStdString(m_monitor.getCurrentFormat()))
GETTER(QString, MirrorOf, QString::fromStdString(m_monitor.getMirrorOf()))
GETTER(QStringList, AvailableModes, [&]() {
    QStringList list;
    for (const auto& s : m_monitor.getAvailableModes())
        list.append(QString::fromStdString(s));
    return list;
}())

#undef GETTER


// --- Setters ---
#define SETTER(type, name, func) \
    void QmlMonitor::set##name(type value) { func; emit updated(); }

SETTER(int, Id, m_monitor.setId(value))
SETTER(const QString&, Name, m_monitor.setName(value.toStdString()))
SETTER(const QString&, Description, m_monitor.setDescription(value.toStdString()))
SETTER(const QString&, Make, m_monitor.setMake(value.toStdString()))
SETTER(const QString&, Model, m_monitor.setModel(value.toStdString()))
SETTER(const QString&, Serial, m_monitor.setSerial(value.toStdString()))
SETTER(int, Width, m_monitor.setWidth(value))
SETTER(int, Height, m_monitor.setHeight(value))
SETTER(double, RefreshRate, m_monitor.setRefreshRate(value))
/*SETTER(int, PositionX, m_monitor.setPositionX(value))*/
SETTER(int, PositionY, m_monitor.setPositionY(value))
SETTER(double, Scale, m_monitor.setScale(value))
SETTER(int, Transform, m_monitor.setTransform(static_cast<core::Transform>(value)))
SETTER(bool, Focused, m_monitor.setFocused(value))
SETTER(bool, DpmsStatus, m_monitor.setDpmsStatus(value))
SETTER(bool, Vrr, m_monitor.setVrrEnabled(value))
SETTER(const QString&, Solitary, m_monitor.setSolitary(value.toStdString()))
SETTER(bool, ActivelyTearing, m_monitor.setActivelyTearing(value))
SETTER(const QString&, DirectScanoutTo, m_monitor.setDirectScanoutTo(value.toStdString()))
SETTER(bool, Disabled, m_monitor.setDisabled(value))
SETTER(const QString&, CurrentFormat, m_monitor.setCurrentFormat(value.toStdString()))
SETTER(const QString&, MirrorOf, m_monitor.setMirrorOf(value.toStdString()))
SETTER(const QStringList&, AvailableModes, {
    std::vector<std::string> vec;
    for (const auto& s : value)
        vec.push_back(s.toStdString());
    m_monitor.setAvailableModes(vec);
})

#undef SETTER

