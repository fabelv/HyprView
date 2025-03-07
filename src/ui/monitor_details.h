#ifndef MONITOR_DETAILS_H
#define MONITOR_DETAILS_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include "../models/monitor.h"

class MonitorDetails : public QWidget {
    Q_OBJECT

public:
    explicit MonitorDetails(QWidget* parent = nullptr);
    void setMonitor(const Monitor& monitor);

signals:
    void monitorUpdated(Monitor monitor);

private:
    Monitor currentMonitor;
    QLineEdit* widthField;
    QLineEdit* heightField;
    QLineEdit* refreshRateField;
    QPushButton* applyButton;

    void updateUI();
    void applyChanges();
};

#endif
