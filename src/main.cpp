#include <QApplication>
#include <vector>
#include "components/main_layout.h"
#include "models/monitor.h"
#include "services/hypr_monitor_manager.h"
#include "utils/hypr_monitor_parser.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    HyprMonitorParser hyprMonitorParser;
    HyprMonitorManager hyprMonitorManager(&hyprMonitorParser);
    std::vector<Monitor> monitors = hyprMonitorManager.getMonitors();

    MainLayout window;
    MonitorView *monitorView = new MonitorView();
    MonitorDetails *monitorDetails = new MonitorDetails();

    monitorView->setMonitors(monitors);
    monitorDetails->clearMonitor();

    window.setMonitorDetails(monitorDetails);
    window.setMonitorView(monitorView);
    
    window.show();

    return app.exec();
}


