#include "main_layout.h"
#include "ui_main_layout.h"

MainLayout::MainLayout(QWidget *parent) : QWidget(parent), ui(new Ui::MainLayout) {
    ui->setupUi(this);
}

MainLayout::~MainLayout() {
    delete ui;
}

void MainLayout::setMonitorView(MonitorView *monitorView) {
    ui->monitorViewWidget->layout()->addWidget(monitorView);
    connect(monitorView, &MonitorView::monitorSelected, monitorDetails, &MonitorDetails::setMonitor);
}

void MainLayout::setMonitorDetails(MonitorDetails *monitorDetails) {
    this->monitorDetails = monitorDetails;
    ui->detailsWidget->layout()->addWidget(monitorDetails);
}



