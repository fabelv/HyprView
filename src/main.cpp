#include "hyprview_core/utils/hypr_monitor_parser.h"
#include "hyprview_core/utils/logger.h"
#include "qtbridge/qml_monitor.h"
#include "qtbridge/qml_monitor_manager.h"
#include "qtbridge/qml_transform_helper.h"
#include "services/hypr_monitor_manager.h"
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <memory>

int main(int argc, char *argv[]) {

  log(core::LogLevel::Info, "Setting up core services...");
  std::unique_ptr<core::HyprMonitorParser> parser =
      std::make_unique<core::HyprMonitorParser>();
  std::unique_ptr<core::HyprMonitorManager> coreManager =
      std::make_unique<core::HyprMonitorManager>(parser.get());

  log(core::LogLevel::Info, "Initial Monitor scan");
  coreManager->scanMonitors();

  log(core::LogLevel::Info, "Initialize QT");
  QGuiApplication app(argc, argv);
  QQmlApplicationEngine engine;

  log(core::LogLevel::Info, "Registering QML types...");
  qmlRegisterType<QmlMonitor>("HyprView", 1, 0, "QmlMonitor");
  std::unique_ptr<QmlMonitorManager> qmlManager =
      std::make_unique<QmlMonitorManager>(coreManager.get());

  log(core::LogLevel::Info, "Exposing context properties...");
  engine.rootContext()->setContextProperty("monitorManager", qmlManager.get());
  qmlRegisterUncreatableType<TransformHelper>("HyprView", 1, 0, "Transform",
                                              "Enum only");

  log(core::LogLevel::Info, "Loading QML UI...");
  engine.load(QUrl::fromLocalFile("src/qml/Main.qml"));

  log(core::LogLevel::Info, "Application running.");
  return app.exec();
}
