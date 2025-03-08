#include "main_window.h"
#include "monitor_view.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QVBoxLayout>
#include <qbrush.h>
#include <qnamespace.h>
#include <qpainter.h>
#include <qpen.h>
#include <qpixmap.h>

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

    // Draw a static grid
    QPen pen(Qt::lightGray, 1, Qt::DashLine);
    for (int x = 0; x <= 800; x += 50) {
        scene->addLine(x, 0, x, 400, pen);  // Vertical lines
    }
    for (int y = 0; y <= 400; y += 50) {
        scene->addLine(0, y, 800, y, pen);  // Horizontal lines
    }

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
