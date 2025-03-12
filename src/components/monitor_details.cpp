#include "monitor_details.h"
#include <QString>

MonitorDetails::MonitorDetails(QWidget *parent) : QWidget(parent), ui(new Ui::MonitorDetails) {
    ui->setupUi(this);

    connect(ui->applyButton, &QPushButton::clicked, this, &MonitorDetails::applyChanges);
}

void MonitorDetails::setMonitor(const Monitor &monitor) {
    currentMonitor = monitor;

    ui->monitorName->setText(QString::fromStdString(monitor.getName()));
    ui->monitorMake->setText(QString::fromStdString(monitor.getMake()));
    ui->monitorModelLabel->setText(QString::fromStdString(monitor.getModel()));
    ui->monitorSerial->setText(QString::fromStdString(monitor.getSerial()));

    ui->positionX->setValue(monitor.getPositionX());
    ui->positionY->setValue(monitor.getPositionY());
    ui->scaleFactor->setValue(monitor.getScale());

    ui->primaryCheckbox->setChecked(monitor.isFocused());
    ui->dpmsCheckbox->setChecked(monitor.getDpmsStatus());
    ui->vrrCheckbox->setChecked(monitor.isVrrEnabled());
    ui->disabledCheckbox->setChecked(monitor.isDisabled());

    ui->resolutionDropdown->clear();
    for (const auto &mode : monitor.getAvailableModes()) {
        ui->resolutionDropdown->addItem(QString::fromStdString(mode));
    }

    // Ensure a valid selection in the resolution dropdown
    if (!monitor.getAvailableModes().empty()) {
        ui->resolutionDropdown->setCurrentIndex(0);
    }
}

void MonitorDetails::clearMonitor() {
    ui->monitorName->clear();
    ui->monitorMake->clear();
    ui->monitorModelLabel->clear();
    ui->monitorSerial->clear();

    ui->positionX->setValue(0);
    ui->positionY->setValue(0);
    ui->scaleFactor->setValue(1.0);

    ui->primaryCheckbox->setChecked(false);
    ui->dpmsCheckbox->setChecked(false);
    ui->vrrCheckbox->setChecked(false);
    ui->disabledCheckbox->setChecked(false);

    ui->resolutionDropdown->clear();
}

void MonitorDetails::applyChanges() {
    currentMonitor = Monitor(
        currentMonitor.getId(),
        currentMonitor.getName(),
        currentMonitor.getDescription(),
        currentMonitor.getMake(),
        currentMonitor.getModel(),
        currentMonitor.getSerial(),
        currentMonitor.getWidth(),
        currentMonitor.getHeight(),
        currentMonitor.getRefreshRate(),
        ui->positionX->value(),
        ui->positionY->value(),
        ui->scaleFactor->value(),
        currentMonitor.getTransform(),
        ui->primaryCheckbox->isChecked(),
        ui->dpmsCheckbox->isChecked(),
        ui->vrrCheckbox->isChecked(),
        currentMonitor.getSolitary(),
        currentMonitor.isActivelyTearing(),
        currentMonitor.getDirectScanoutTo(),
        ui->disabledCheckbox->isChecked(),
        currentMonitor.getCurrentFormat(),
        currentMonitor.getMirrorOf(),
        currentMonitor.getAvailableModes()
    );

    emit monitorUpdated(currentMonitor);
}

