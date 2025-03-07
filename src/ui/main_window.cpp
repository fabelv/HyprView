#include "main_window.h"
#include "monitor_view.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QVBoxLayout>

MainWindow::MainWindow(HyprMonitorManager* monitorManager, QWidget *parent)
    : QMainWindow(parent), monitorManager(monitorManager) {

    setupUI();
    loadMonitors();
}

void MainWindow::setupUI() {
    QWidget* centralWidget = new QWidget(this);
    QVBoxLayout* layout = new QVBoxLayout(centralWidget);

    scene = new QGraphicsScene(this);
    monitorView = new QGraphicsView(scene, this);
    monitorView->setSceneRect(0, 0, 800, 400);

    monitorDetails = new MonitorDetails(this);

    layout->addWidget(monitorView);
    layout->addWidget(monitorDetails);

    setCentralWidget(centralWidget);
}

void MainWindow::loadMonitors() {
    monitors = monitorManager->getMonitors();

    for (auto& monitor : monitors) {
        MonitorView* monitorItem = new MonitorView(monitor);
        scene->addItem(monitorItem);

        connect(monitorItem, &MonitorView::monitorSelected, this, &MainWindow::onMonitorSelected);
    }
}

void MainWindow::onMonitorSelected(Monitor monitor) {
    monitorDetails->setMonitor(monitor);
}
