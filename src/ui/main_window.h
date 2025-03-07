#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QVBoxLayout>
#include <QPushButton>
#include <vector>
#include "../services/hypr_monitor_manager.h"
#include "monitor_details.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(HyprMonitorManager* monitorManager, QWidget *parent = nullptr);

private:
    QGraphicsView* monitorView;
    QGraphicsScene* scene;
    MonitorDetails* monitorDetails;
    HyprMonitorManager* monitorManager;
    
    std::vector<Monitor> monitors;
    
    void loadMonitors();
    void setupUI();

private slots:
    void onMonitorSelected(Monitor monitor);
};

#endif
