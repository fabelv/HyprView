#ifndef MAIN_LAYOUT_H
#define MAIN_LAYOUT_H

#include <QWidget>
#include "monitor_view.h"
#include "monitor_details.h"

namespace Ui {
class MainLayout;
}

class MainLayout : public QWidget {
    Q_OBJECT

public:
    explicit MainLayout(QWidget *parent = nullptr);
    ~MainLayout();

    void setMonitorView(MonitorView *monitorView);
    void setMonitorDetails(MonitorDetails *monitorDetails);

private:
    Ui::MainLayout *ui;
    MonitorDetails *monitorDetails;
};

#endif

