#pragma once

#include <QObject>
#include <QString>
#include <QStringList>
#include "../core/models/monitor.h"

class QmlMonitor : public QObject {
    Q_OBJECT

    Q_PROPERTY(int id READ getId WRITE setId NOTIFY updated)
    Q_PROPERTY(QString name READ getName WRITE setName NOTIFY updated)
    Q_PROPERTY(QString description READ getDescription WRITE setDescription NOTIFY updated)
    Q_PROPERTY(QString make READ getMake WRITE setMake NOTIFY updated)
    Q_PROPERTY(QString model READ getModel WRITE setModel NOTIFY updated)
    Q_PROPERTY(QString serial READ getSerial WRITE setSerial NOTIFY updated)
    Q_PROPERTY(int width READ getWidth WRITE setWidth NOTIFY updated)
    Q_PROPERTY(int height READ getHeight WRITE setHeight NOTIFY updated)
    Q_PROPERTY(double refreshRate READ getRefreshRate WRITE setRefreshRate NOTIFY updated)
    Q_PROPERTY(int positionX READ getPositionX WRITE setPositionX NOTIFY updated)
    Q_PROPERTY(int positionY READ getPositionY WRITE setPositionY NOTIFY updated)
    Q_PROPERTY(double scale READ getScale WRITE setScale NOTIFY updated)
    Q_PROPERTY(int transform READ getTransform WRITE setTransform NOTIFY updated)
    Q_PROPERTY(bool focused READ getFocused WRITE setFocused NOTIFY updated)
    Q_PROPERTY(bool dpmsStatus READ getDpmsStatus WRITE setDpmsStatus NOTIFY updated)
    Q_PROPERTY(bool vrr READ getVrr WRITE setVrr NOTIFY updated)
    Q_PROPERTY(QString solitary READ getSolitary WRITE setSolitary NOTIFY updated)
    Q_PROPERTY(bool activelyTearing READ getActivelyTearing WRITE setActivelyTearing NOTIFY updated)
    Q_PROPERTY(QString directScanoutTo READ getDirectScanoutTo WRITE setDirectScanoutTo NOTIFY updated)
    Q_PROPERTY(bool disabled READ isDisabled WRITE setDisabled NOTIFY updated)
    Q_PROPERTY(QString currentFormat READ getCurrentFormat WRITE setCurrentFormat NOTIFY updated)
    Q_PROPERTY(QString mirrorOf READ getMirrorOf WRITE setMirrorOf NOTIFY updated)
    Q_PROPERTY(QStringList availableModes READ getAvailableModes WRITE setAvailableModes NOTIFY updated)

public:
    explicit QmlMonitor(core::Monitor monitor, QObject* parent = nullptr);

    Q_INVOKABLE QString generateCurrentMode() const;
    Q_INVOKABLE void applyModeString(const QString& mode);
    const core::Monitor& internal() const;

    // Getters
    int getId() const;
    QString getName() const;
    QString getDescription() const;
    QString getMake() const;
    QString getModel() const;
    QString getSerial() const;
    int getWidth() const;
    int getHeight() const;
    double getRefreshRate() const;
    int getPositionX() const;
    int getPositionY() const;
    double getScale() const;
    int getTransform() const;
    bool getFocused() const;
    bool getDpmsStatus() const;
    bool getVrr() const;
    QString getSolitary() const;
    bool getActivelyTearing() const;
    QString getDirectScanoutTo() const;
    bool isDisabled() const;
    QString getCurrentFormat() const;
    QString getMirrorOf() const;
    QStringList getAvailableModes() const;

    // Setters
    void setId(int);
    void setName(const QString&);
    void setDescription(const QString&);
    void setMake(const QString&);
    void setModel(const QString&);
    void setSerial(const QString&);
    void setWidth(int);
    void setHeight(int);
    void setRefreshRate(double);
    void setPositionX(int);
    void setPositionY(int);
    void setScale(double);
    void setTransform(int);
    void setFocused(bool);
    void setDpmsStatus(bool);
    void setVrr(bool);
    void setSolitary(const QString&);
    void setActivelyTearing(bool);
    void setDirectScanoutTo(const QString&);
    void setDisabled(bool);
    void setCurrentFormat(const QString&);
    void setMirrorOf(const QString&);
    void setAvailableModes(const QStringList&);

signals:
    void updated();

private:
    core::Monitor m_monitor;
};
