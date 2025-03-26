#pragma once

#include <QObject>
#include <QString>
#include <QStringList>

class Monitor : public QObject {
    Q_OBJECT

    Q_PROPERTY(int id READ getId WRITE setId NOTIFY changed)
    Q_PROPERTY(QString name READ getName WRITE setName NOTIFY changed)
    Q_PROPERTY(QString description READ getDescription WRITE setDescription NOTIFY changed)
    Q_PROPERTY(QString make READ getMake WRITE setMake NOTIFY changed)
    Q_PROPERTY(QString model READ getModel WRITE setModel NOTIFY changed)
    Q_PROPERTY(QString serial READ getSerial WRITE setSerial NOTIFY changed)
    Q_PROPERTY(int width READ getWidth WRITE setWidth NOTIFY changed)
    Q_PROPERTY(int height READ getHeight WRITE setHeight NOTIFY changed)
    Q_PROPERTY(double refreshRate READ getRefreshRate WRITE setRefreshRate NOTIFY changed)
    Q_PROPERTY(int positionX READ getPositionX WRITE setPositionX NOTIFY changed)
    Q_PROPERTY(int positionY READ getPositionY WRITE setPositionY NOTIFY changed)
    Q_PROPERTY(double scale READ getScale WRITE setScale NOTIFY changed)
    Q_PROPERTY(int transform READ getTransform WRITE setTransform NOTIFY changed)
    Q_PROPERTY(bool focused READ isFocused WRITE setFocused NOTIFY changed)
    Q_PROPERTY(bool dpmsStatus READ getDpmsStatus WRITE setDpmsStatus NOTIFY changed)
    Q_PROPERTY(bool vrr READ isVrrEnabled WRITE setVrrEnabled NOTIFY changed)
    Q_PROPERTY(QString solitary READ getSolitary WRITE setSolitary NOTIFY changed)
    Q_PROPERTY(bool activelyTearing READ isActivelyTearing WRITE setActivelyTearing NOTIFY changed)
    Q_PROPERTY(QString directScanoutTo READ getDirectScanoutTo WRITE setDirectScanoutTo NOTIFY changed)
    Q_PROPERTY(bool disabled READ isDisabled WRITE setDisabled NOTIFY changed)
    Q_PROPERTY(QString currentFormat READ getCurrentFormat WRITE setCurrentFormat NOTIFY changed)
    Q_PROPERTY(QString mirrorOf READ getMirrorOf WRITE setMirrorOf NOTIFY changed)
    Q_PROPERTY(QStringList availableModes READ getAvailableModes WRITE setAvailableModes NOTIFY changed)

public:
    explicit Monitor(QObject* parent = nullptr);

    QString toString() const;

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
    bool isFocused() const;
    bool getDpmsStatus() const;
    bool isVrrEnabled() const;
    QString getSolitary() const;
    bool isActivelyTearing() const;
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
    void setVrrEnabled(bool);
    void setSolitary(const QString&);
    void setActivelyTearing(bool);
    void setDirectScanoutTo(const QString&);
    void setDisabled(bool);
    void setCurrentFormat(const QString&);
    void setMirrorOf(const QString&);
    void setAvailableModes(const QStringList&);

signals:
    void changed();

private:
    int id;
    QString name;
    QString description;
    QString make;
    QString model;
    QString serial;
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
    QString solitary;
    bool activelyTearing;
    QString directScanoutTo;
    bool disabled;
    QString currentFormat;
    QString mirrorOf;
    QStringList availableModes;
};

