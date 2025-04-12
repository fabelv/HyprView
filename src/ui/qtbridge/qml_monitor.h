#pragma once

#include <QObject>
#include <QString>
#include <QStringList>

#include "hyprview_core/models/monitor.h"

namespace qtbridge {

class QmlMonitor : public QObject {
    Q_OBJECT

    // qt properties
    Q_PROPERTY(int id_ READ getId WRITE setId NOTIFY updated)
    Q_PROPERTY(QString name_ READ getName WRITE setName NOTIFY updated)
    Q_PROPERTY(QString description_ READ getDescription WRITE setDescription NOTIFY updated)
    Q_PROPERTY(QString make_ READ getMake WRITE setMake NOTIFY updated)
    Q_PROPERTY(QString model_ READ getModel WRITE setModel NOTIFY updated)
    Q_PROPERTY(QString serial_ READ getSerial WRITE setSerial NOTIFY updated)
    Q_PROPERTY(int width_ READ getWidth WRITE setWidth NOTIFY updated)
    Q_PROPERTY(int height_ READ getHeight WRITE setHeight NOTIFY updated)
    Q_PROPERTY(double refreshRate_ READ getRefreshRate WRITE setRefreshRate NOTIFY updated)
    Q_PROPERTY(int positionX_ READ getPositionX WRITE setPositionX NOTIFY updated)
    Q_PROPERTY(int positionY_ READ getPositionY WRITE setPositionY NOTIFY updated)
    Q_PROPERTY(double scale_ READ getScale WRITE setScale NOTIFY updated)
    Q_PROPERTY(int transform_ READ getTransform WRITE setTransform NOTIFY updated)
    Q_PROPERTY(bool dpmsStatus_ READ getDpmsStatus WRITE setDpmsStatus NOTIFY updated)
    Q_PROPERTY(bool vrr_ READ getVrr WRITE setVrr NOTIFY updated)
    Q_PROPERTY(QString solitary_ READ getSolitary WRITE setSolitary NOTIFY updated)
    Q_PROPERTY(
        bool activelyTearing_ READ getActivelyTearing WRITE setActivelyTearing NOTIFY updated)
    Q_PROPERTY(
        QString directScanoutTo_ READ getDirectScanoutTo WRITE setDirectScanoutTo NOTIFY updated)
    Q_PROPERTY(bool disabled_ READ getDisabled WRITE setDisabled NOTIFY updated)
    Q_PROPERTY(QString currentFormat_ READ getCurrentFormat WRITE setCurrentFormat NOTIFY updated)
    Q_PROPERTY(QString mirrorOf_ READ getMirrorOf WRITE setMirrorOf NOTIFY updated)
    Q_PROPERTY(
        QStringList availableModes_ READ getAvailableModes WRITE setAvailableModes NOTIFY updated)

   public:
    // constructors
    explicit QmlMonitor(core::Monitor* monitor, QObject* parent = nullptr);

    // core methods
    Q_INVOKABLE QString generateCurrentMode() const;
    Q_INVOKABLE void applyModeString(const QString& mode);

    // accessors
    auto getMonitor() const -> const core::Monitor*;

    auto getId() const -> const int;
    auto setId(int) -> void;

    auto getName() const -> const QString;
    auto setName(const QString&) -> void;

    auto getDescription() const -> const QString;
    auto setDescription(const QString&) -> void;

    auto getMake() const -> const QString;
    auto setMake(const QString&) -> void;

    auto getModel() const -> const QString;
    auto setModel(const QString&) -> void;

    auto getSerial() const -> const QString;
    auto setSerial(const QString&) -> void;

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

    auto getTransform() const -> const int;
    auto setTransform(int) -> void;

    auto getFocused() const -> const bool;
    auto setFocused(bool) -> void;

    auto getDpmsStatus() const -> const bool;
    auto setDpmsStatus(bool) -> void;

    auto getVrr() const -> const bool;
    auto setVrr(bool) -> void;

    auto getSolitary() const -> const QString;
    auto setSolitary(const QString&) -> void;

    auto getActivelyTearing() const -> const bool;
    auto setActivelyTearing(bool) -> void;

    auto getDirectScanoutTo() const -> const QString;
    auto setDirectScanoutTo(const QString&) -> void;

    auto getDisabled() const -> const bool;
    auto setDisabled(bool) -> void;

    auto getCurrentFormat() const -> const QString;
    auto setCurrentFormat(const QString&) -> void;

    auto getMirrorOf() const -> const QString;
    auto setMirrorOf(const QString&) -> void;

    auto getAvailableModes() const -> const QStringList;
    auto setAvailableModes(const QStringList&) -> void;

   signals:
    void updated();
    void positionUpdatedByDragAndDrop();

   private:
    core::Monitor* monitor_;
};

}  // namespace qtbridge
