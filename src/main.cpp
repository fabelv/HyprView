#include <QDir>
#include <QFile>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <memory>

#include "hyprview_core/parsers/hypr_monitor_parser.h"
#include "managers/hypr_monitor_manager.h"
#include "ui/qtbridge/qml_monitor.h"
#include "ui/qtbridge/qml_monitor_helpers.h"
#include "ui/qtbridge/qml_monitor_manager.h"
#include "ui/qtbridge/qml_transform_helper.h"

int main(int argc, char *argv[]) {
    auto parser = std::make_shared<core::HyprMonitorParser>();
    auto coreManager = std::make_unique<core::HyprMonitorManager>(parser);

    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    qmlRegisterType<qtbridge::QmlMonitor>("HyprView", 1, 0, "QmlMonitor");
    auto qmlManager = std::make_unique<qtbridge::QmlMonitorManager>(coreManager.get());
    auto qmlMonitorHelpers = std::make_unique<qtbridge::QmlMonitorHelpers>();

    engine.rootContext()->setContextProperty("monitorManager", qmlManager.get());
    engine.rootContext()->setContextProperty("monitorHelpers", qmlMonitorHelpers.get());
    qmlRegisterSingletonType<TransformHelper>(
        "Core", 1, 0, "TransformHelper",
        [](QQmlEngine *, QJSEngine *) { return new TransformHelper; });

    QString devQmlPath =
        QDir::cleanPath(QCoreApplication::applicationDirPath() + "/../src/ui/qml/Main.qml");
    QString installQmlPath =
        QDir::cleanPath(QCoreApplication::applicationDirPath() + "/../share/hyprview/qml/Main.qml");

    QString qmlPath;
    if (QFile::exists(devQmlPath)) {
        qmlPath = devQmlPath;
    } else {
        qmlPath = installQmlPath;
    }

    engine.load(QUrl::fromLocalFile(qmlPath));

    return app.exec();
}
