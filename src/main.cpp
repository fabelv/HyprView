#include "hyprview_core/parsers/hypr_monitor_parser.h"
#include "hyprview_core/utils/logger.h"
#include "managers/hypr_monitor_manager.h"
#include "ui/qtbridge/qml_monitor.h"
#include "ui/qtbridge/qml_monitor_manager.h"
#include "ui/qtbridge/qml_transform_helper.h"
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <memory>

int main(int argc, char *argv[]) {

  log(core::LogLevel::Info, "Setting up core services...");
  auto parser = std::make_shared<core::HyprMonitorParser>();
  auto coreManager = std::make_unique<core::HyprMonitorManager>(parser);

  log(core::LogLevel::Info, "Initial Monitor scan");
  coreManager->scanMonitors();

  log(core::LogLevel::Info, "Initialize QT");
  QGuiApplication app(argc, argv);
  QQmlApplicationEngine engine;

  log(core::LogLevel::Info, "Registering QML types...");
  qmlRegisterType<qtbridge::QmlMonitor>("HyprView", 1, 0, "QmlMonitor");
  auto qmlManager =
      std::make_unique<qtbridge::QmlMonitorManager>(coreManager.get());

  log(core::LogLevel::Info, "Exposing context properties...");
  engine.rootContext()->setContextProperty("monitorManager", qmlManager.get());
  qmlRegisterUncreatableType<TransformHelper>("HyprView", 1, 0, "Transform",
                                              "Enum only");

  log(core::LogLevel::Info, "Loading QML UI...");
  engine.load(QUrl::fromLocalFile("src/ui/qml/Main.qml"));

  log(core::LogLevel::Info, "Application running.");
  return app.exec();
}
