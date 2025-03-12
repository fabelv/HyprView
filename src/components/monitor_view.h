#ifndef MONITOR_VIEW_H
#define MONITOR_VIEW_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <vector>
#include "../models/monitor.h"
#include "monitor_item.h"

class MonitorView : public QGraphicsView {
    Q_OBJECT

public:
    explicit MonitorView(QWidget *parent = nullptr);
    void setMonitors(const std::vector<Monitor>& monitors);

signals:
    void monitorSelected(Monitor monitor);

private:
    QGraphicsScene* scene;
};

#endif

