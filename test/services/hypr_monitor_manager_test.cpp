#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <hyprview_core/models/monitor.h>
#include <hyprview_core/parsers/hypr_monitor_parser.h>
#include <../../../src/managers/hypr_monitor_manager.h>
#include <memory>

using namespace core;
using ::testing::Return;
using ::testing::_;

// --- Mock parser class ---
class MockParser : public HyprMonitorParser {
public:
    MOCK_METHOD(std::vector<Monitor>, parseMonitorsFromJson, (const std::string&), (const));
};

// --- Helper: make a test monitor ---
Monitor makeTestMonitor(const std::string& name = "HDMI-A-1", int width = 1920, int height = 1080) {
    Monitor m;
    m.setName(name);
    m.setWidth(width);
    m.setHeight(height);
    m.setRefreshRate(60.0);
    m.setPositionX(0);
    m.setPositionY(0);
    m.setScale(1.0);
    m.setTransform(Transform::Normal);
    m.setVrrEnabled(false);
    m.setMirrorOf("");
    m.setDisabled(true);
    return m;
}

// --- Scoped override of std::system ---
int systemCallCount = 0;
std::string lastCommand;
std::vector<std::string> allCommands;

extern "C" int __real_system(const char*);
extern "C" int __wrap_system(const char* cmd) {
    lastCommand = cmd;
    allCommands.push_back(cmd);
    systemCallCount++;
    return 0; // Simulate success
}

// --- Tests ---
TEST(HyprMonitorManagerTest, ConstructorInitializesCorrectly) {
    auto parser = std::make_shared<MockParser>();
    HyprMonitorManager manager(parser);
    EXPECT_EQ(manager.getMonitors().size(), 0);
}

TEST(HyprMonitorManagerTest, ScanMonitorsUsesParser) {
    auto parser = std::make_shared<MockParser>();
    HyprMonitorManager manager(parser);

    std::vector<Monitor> fakeMonitors = { makeTestMonitor("DP-1") };
    EXPECT_CALL(*parser, parseMonitorsFromJson(_)).WillOnce(Return(fakeMonitors));

    manager.scanMonitors();
    EXPECT_EQ(manager.getMonitors().size(), 1);
    EXPECT_EQ(manager.getMonitors()[0].getName(), "DP-1");
}

TEST(HyprMonitorManagerTest, ApplyMonitorConfigurationGeneratesCommandForEnabledMonitor) {
    std::shared_ptr<MockParser> parser;
    HyprMonitorManager manager(parser);

    Monitor m = makeTestMonitor("DP-1", 1920, 1080);
    m.setRefreshRate(75.5);
    m.setTransform(Transform::Rotate90);
    m.setVrrEnabled(true);
    m.setMirrorOf("none");
    m.setDisabled(false);

    manager.getMonitors().push_back(m);
    systemCallCount = 0;
    lastCommand = "";
    allCommands.clear();

    bool result = manager.applyMonitorConfiguration();

    EXPECT_TRUE(result);
    EXPECT_EQ(systemCallCount, 1);
    EXPECT_THAT(lastCommand, ::testing::HasSubstr("hyprctl keyword monitor DP-1,1920x1080@75.50"));
    EXPECT_THAT(lastCommand, ::testing::HasSubstr("transform, 1"));
    EXPECT_THAT(lastCommand, ::testing::HasSubstr("vrr, 1"));
    EXPECT_THAT(lastCommand, ::testing::Not(::testing::HasSubstr("disable")));
}

TEST(HyprMonitorManagerTest, ApplyMonitorConfigurationGeneratesCommandForDisabledMonitor) {
    std::shared_ptr<MockParser> parser;
    HyprMonitorManager manager(parser);

    Monitor m = makeTestMonitor("HDMI-A-1");
    m.setDisabled(true);

    manager.getMonitors().push_back(m);
    systemCallCount = 0;
    lastCommand = "";
    allCommands.clear();

    bool result = manager.applyMonitorConfiguration();

    EXPECT_TRUE(result);
    EXPECT_EQ(systemCallCount, 1);
    EXPECT_THAT(lastCommand, ::testing::HasSubstr("hyprctl keyword monitor HDMI-A-1,disable"));
}

TEST(HyprMonitorManagerTest, ApplyMonitorConfigurationHandlesMultipleMonitors) {
    std::shared_ptr<MockParser> parser;
    HyprMonitorManager manager(parser);

    Monitor m1 = makeTestMonitor("DP-1");
    m1.setDisabled(false);
    Monitor m2 = makeTestMonitor("HDMI-A-1");
    m2.setDisabled(true);

    manager.getMonitors().push_back(m1);
    manager.getMonitors().push_back(m2);

    systemCallCount = 0;
    allCommands.clear();

    bool result = manager.applyMonitorConfiguration();

    EXPECT_TRUE(result);
    EXPECT_EQ(systemCallCount, 2);
    EXPECT_THAT(allCommands[0], ::testing::HasSubstr("DP-1"));
    EXPECT_THAT(allCommands[1], ::testing::HasSubstr("HDMI-A-1,disable"));
}


TEST(HyprMonitorManagerTest, RevertMonitorConfigurationUsesBackup) {
    std::shared_ptr<MockParser> parser;
    HyprMonitorManager manager(parser);

    std::vector<Monitor> backupMonitors = {
        makeTestMonitor("DP-1", 1920, 1080)
    };

    EXPECT_CALL(*parser, parseMonitorsFromJson(_)).WillOnce(Return(backupMonitors));

    manager.scanMonitors();              // Fills both current + backup
    manager.getMonitors()[0].setName("Changed");

    systemCallCount = 0;
    lastCommand.clear();

    bool result = manager.revertMonitorConfiguration();

    EXPECT_TRUE(result);
    EXPECT_EQ(systemCallCount, 1);
    EXPECT_THAT(lastCommand, ::testing::HasSubstr("DP-1"));
}

