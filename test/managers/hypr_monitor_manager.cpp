#include "../../src/managers/hypr_monitor_manager.h"
#include "hyprview_core/models/monitor.h"
#include "hyprview_core/parsers/monitor_parser.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace core;
using ::testing::Return;

class MockMonitorParser : public MonitorParser {
public:
  MOCK_METHOD(std::vector<Monitor>, parseMonitorsFromJson,
              (const std::string &), (override));
};

class TestableHyprMonitorManager : public HyprMonitorManager {
public:
  using HyprMonitorManager::HyprMonitorManager;

  std::string testJson;
  std::vector<std::string> commandsRun;
  bool commandSuccess = true;

  void testSetMonitors(std::vector<Monitor> &monitors) {
    setMonitors(monitors);
  }

protected:
  std::string fetchMonitorJson() override { return testJson; }

  bool executeCommand(const std::string &cmd) override {
    commandsRun.push_back(cmd);
    return commandSuccess;
  }
};

TEST(HyprMonitorManagerTest, ParsesJsonCorrectlyInScanMonitors) {
  auto parser = std::make_shared<MockMonitorParser>();
  TestableHyprMonitorManager manager(parser);

  Monitor monitor;
  monitor.setName("DP-1");

  manager.testJson = R"([{"id":0,"name":"DP-1"}])";

  EXPECT_CALL(*parser, parseMonitorsFromJson(manager.testJson))
      .WillOnce(Return(std::vector<Monitor>{monitor}));

  manager.scanMonitors();

  auto &monitors = manager.getMonitors();
  ASSERT_EQ(monitors.size(), 1);
  EXPECT_EQ(monitors[0].getName(), "DP-1");
}

TEST(HyprMonitorManagerTest, BuildsCommandCorrectlyForMonitor) {
  auto parser = std::make_shared<MockMonitorParser>();
  TestableHyprMonitorManager manager(parser);

  Monitor m;
  m.setName("HDMI-A-1");
  m.setWidth(1920);
  m.setHeight(1080);
  m.setRefreshRate(60.0);
  m.setPositionX(0);
  m.setPositionY(0);
  m.setScale(1.0);
  m.setTransform(Transform::Normal);
  m.setVrrEnabled(false);
  m.setMirrorOf("none");

  std::vector<Monitor> monitors = {m};
  manager.testSetMonitors(monitors);

  bool success = manager.applyMonitorConfiguration();
  EXPECT_TRUE(success);
  ASSERT_EQ(manager.commandsRun.size(), 1);
  EXPECT_THAT(manager.commandsRun[0],
              ::testing::HasSubstr("HDMI-A-1,1920x1080@60.00,0x0,1.00"));
}

TEST(HyprMonitorManagerTest, CommandFailureReturnsFalse) {
  auto parser = std::make_shared<MockMonitorParser>();
  TestableHyprMonitorManager manager(parser);

  Monitor m;
  m.setName("DP-2");
  m.setWidth(1280);
  m.setHeight(720);
  m.setRefreshRate(75.0);
  m.setPositionX(100);
  m.setPositionY(100);
  m.setScale(1.25);
  m.setTransform(Transform::Flipped);
  m.setVrrEnabled(true);
  m.setMirrorOf("none");

  std::vector<Monitor> monitors = {m};
  manager.testSetMonitors(monitors);

  manager.commandSuccess = false;
  bool success = manager.applyMonitorConfiguration();

  EXPECT_FALSE(success);
  ASSERT_EQ(manager.commandsRun.size(), 1);
}
