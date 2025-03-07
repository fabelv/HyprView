#include "services/hypr_monitor_manager.h"
#include "ui/main_window.h"
#include "utils/hypr_monitor_parser.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    HyprMonitorParser parser;
    HyprMonitorManager monitorManager(&parser);
    MainWindow window(&monitorManager);
    window.show();
    return app.exec();
}

