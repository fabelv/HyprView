#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "core/utils/logger.h"
#include "core/utils/hypr_monitor_parser.h"
#include "qtbridge/qml_monitor_helpers.h"
#include "qtbridge/qml_monitor_manager.h"
#include "qtbridge/qml_transform_helper.h"
#include "services/hypr_monitor_manager.h"
#include "qtbridge/qml_monitor.h"

int main(int argc, char *argv[]) {

    log(core::LogLevel::Info, "Setting up core services...");
    auto* parser = new core::HyprMonitorParser();
    auto* coreManager = new core::HyprMonitorManager(parser);

    log(core::LogLevel::Info, "Initial Monitor scan");
    coreManager->scanMonitors();

    log(core::LogLevel::Info, "Initialize QT");
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    log(core::LogLevel::Info, "Registering QML types...");
    qmlRegisterType<QmlMonitor>("HyprView", 1, 0, "QmlMonitor");
    auto* qmlManager = new QmlMonitorManager(coreManager);
    auto* qmlMonitorHelpers = new QmlMonitorHelpers();

    log(core::LogLevel::Info, "Exposing context properties...");
    engine.rootContext()->setContextProperty("monitorManager", qmlManager);
    engine.rootContext()->setContextProperty("monitorHelpers", qmlMonitorHelpers);
    qmlRegisterUncreatableType<TransformHelper>("HyprView", 1, 0, "Transform", "Enum only");

    log(core::LogLevel::Info, "Loading QML UI...");
    engine.load(QUrl::fromLocalFile("src/qml/Main.qml"));

    if (engine.rootObjects().isEmpty()) {
        log(core::LogLevel::Error, "Failed to load QML root object.");
        return -1;
    }

    log(core::LogLevel::Info, "Application running.");
    return app.exec();
}

