#include "monitor_details.h"
#include <QVBoxLayout>
#include <QFormLayout>

MonitorDetails::MonitorDetails(QWidget* parent) 
     : QWidget(parent), currentMonitor() {
    QVBoxLayout* layout = new QVBoxLayout(this);
    QFormLayout* formLayout = new QFormLayout();

    widthField = new QLineEdit(this);
    heightField = new QLineEdit(this);
    refreshRateField = new QLineEdit(this);
    applyButton = new QPushButton("Apply", this);

    formLayout->addRow("Width:", widthField);
    formLayout->addRow("Height:", heightField);
    formLayout->addRow("Refresh Rate:", refreshRateField);

    layout->addLayout(formLayout);
    layout->addWidget(applyButton);

    connect(applyButton, &QPushButton::clicked, this, &MonitorDetails::applyChanges);
}

void MonitorDetails::setMonitor(const Monitor& monitor) {
    currentMonitor = monitor;
    updateUI();
}

void MonitorDetails::updateUI() {
    widthField->setText(QString::number(currentMonitor.getWidth()));
    heightField->setText(QString::number(currentMonitor.getHeight()));
    refreshRateField->setText(QString::number(currentMonitor.getRefreshRate()));
}

void MonitorDetails::applyChanges() {
    currentMonitor = Monitor(
        currentMonitor.getId(),
        currentMonitor.getName(),
        currentMonitor.getDescription(),
        currentMonitor.getMake(),
        currentMonitor.getModel(),
        currentMonitor.getSerial(),
        widthField->text().toInt(),
        heightField->text().toInt(),
        refreshRateField->text().toDouble(),
        currentMonitor.getPositionX(),
        currentMonitor.getPositionY(),
        currentMonitor.getScale(),
        currentMonitor.getTransform(),
        currentMonitor.isFocused(),
        currentMonitor.getDpmsStatus(),
        currentMonitor.isVrrEnabled(),
        currentMonitor.getSolitary(),
        currentMonitor.isActivelyTearing(),
        currentMonitor.getDirectScanoutTo(),
        currentMonitor.isDisabled(),
        currentMonitor.getCurrentFormat(),
        currentMonitor.getMirrorOf(),
        currentMonitor.getAvailableModes()
    );

    emit monitorUpdated(currentMonitor);
}
