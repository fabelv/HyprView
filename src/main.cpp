#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "core/utils/logger.h"
#include "core/utils/hypr_monitor_parser.h"
#include "qml/qml_transform_helper.h"
#include "services/hypr_monitor_manager.h"
#include "qtbridge/qml_monitor.h"
#include "qtbridge/qml_monitor_manager.h"

int main(int argc, char *argv[]) {
    log(core::LogLevel::Info, "Starting HyprView...");

    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    log(core::LogLevel::Info, "Registering QML types...");
    qmlRegisterType<QmlMonitor>("HyprView", 1, 0, "QmlMonitor");

    log(core::LogLevel::Info, "Setting up core services...");
    auto* parser = new core::HyprMonitorParser();
    auto* coreManager = new core::HyprMonitorManager(parser);
    auto* qmlManager = new QmlMonitorManager(coreManager);

    log(core::LogLevel::Info, "Fetching monitor list...");
    QList<QObject*> qmlMonitors = qmlManager->getMonitors();
    QObject* selected = qmlMonitors.isEmpty() ? nullptr : qmlMonitors.first();

    log(core::LogLevel::Debug, "Found " + std::to_string(qmlMonitors.size()) + " monitor(s).");
    if (auto* selectedMonitor = qobject_cast<QmlMonitor*>(selected)) {
        log(core::LogLevel::Debug, "Selected Monitor: " + selectedMonitor->getName().toStdString());
    } else {
        log(core::LogLevel::Debug, "Selected Monitor is null or not a QmlMonitor.");
    }

    log(core::LogLevel::Info, "Exposing context properties...");
    engine.rootContext()->setContextProperty("monitorManager", qmlManager);
    engine.rootContext()->setContextProperty("monitors", QVariant::fromValue(qmlMonitors));
    engine.rootContext()->setContextProperty("selectedMonitor", selected);
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

