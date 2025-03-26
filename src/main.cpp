#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "utils/hypr_monitor_parser.h"
#include "services/hypr_monitor_manager.h"
#include "models/monitor.h"

int main(int argc, char *argv[]) {
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    // --- Get monitors from hyprctl ---
    HyprMonitorParser parser;
    HyprMonitorManager manager(&parser);
    QList<Monitor*> monitors = manager.getMonitors();

    // --- Expose monitor list to QML ---
    engine.rootContext()->setContextProperty(
        "monitors", QVariant::fromValue(QList<QObject*>(monitors.begin(), monitors.end()))
    );

    // --- Expose one selected monitor to QML ---
    engine.rootContext()->setContextProperty(
        "selectedMonitor", monitors.isEmpty() ? nullptr : monitors.first()
    );

    // --- Load QML UI ---
    engine.load(QUrl::fromLocalFile("src/qml/Main.qml"));

    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}

