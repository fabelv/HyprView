#ifndef MONITOR_DETAILS_H
#define MONITOR_DETAILS_H

#include <QWidget>
#include "ui_monitor_details.h"
#include "../models/monitor.h"

class MonitorDetails : public QWidget {
    Q_OBJECT

public:
    explicit MonitorDetails(QWidget *parent = nullptr);
    void setMonitor(const Monitor &monitor);
    void clearMonitor();

signals:
    void monitorUpdated(const Monitor &monitor);

private slots:
    void applyChanges();

private:
    Ui::MonitorDetails *ui;
    Monitor currentMonitor;
};

#endif

