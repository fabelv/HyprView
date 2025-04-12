#include "hyprview_core/managers/monitor_manager.h"
#include "hyprview_core/models/monitor.h"
#include <gtest/gtest.h>
#include <memory>
#include <vector>

using namespace core;

class TestableMonitorManager : public core::MonitorManager {
public:
    explicit TestableMonitorManager(std::shared_ptr<core::MonitorParser> parser)
        : core::MonitorManager(parser) {}

    void scanMonitors() override {}
    bool applyMonitorConfiguration() override { return true; }
    bool revertMonitorConfiguration() override { return true; }

    void testSetMonitors(std::vector<core::Monitor>& monitors) {
        setMonitors(monitors);
    }

    std::vector<core::Monitor>& testGetPreUserEditMonitors() {
        return getPreUserEditMonitors();
    }
};



TEST(MonitorManagerTest, ThrowsOnEmptySetMonitors) {
    TestableMonitorManager manager(nullptr);
    std::vector<core::Monitor> empty;

    EXPECT_THROW(manager.testSetMonitors(empty), std::invalid_argument);
}

TEST(MonitorManagerTest, StoresSingleMonitorCorrectly) {
    TestableMonitorManager manager(nullptr);

    Monitor m;
    m.setId(1);
    m.setName("HDMI-A-1");
    m.setWidth(1920);
    m.setHeight(1080);

    std::vector<Monitor> monitors = { m };
    manager.testSetMonitors(monitors);

    auto& current = manager.getMonitors();
    auto& preEdit = manager.testGetPreUserEditMonitors();

    ASSERT_EQ(current.size(), 1);
    EXPECT_EQ(current[0].getId(), 1);
    EXPECT_EQ(current[0].getName(), "HDMI-A-1");
    EXPECT_EQ(current[0].getWidth(), 1920);
    EXPECT_EQ(current[0].getHeight(), 1080);

    ASSERT_EQ(preEdit.size(), 1);
    EXPECT_EQ(preEdit[0].getName(), "HDMI-A-1");
}

TEST(MonitorManagerTest, StoresMultipleMonitorsCorrectly) {
    TestableMonitorManager manager(nullptr);

    Monitor m1;
    m1.setId(1);
    m1.setName("eDP-1");

    Monitor m2;
    m2.setId(2);
    m2.setName("DP-1");

    std::vector<Monitor> monitors = { m1, m2 };
    manager.testSetMonitors(monitors);

    auto& current = manager.getMonitors();
    auto& preEdit = manager.testGetPreUserEditMonitors();

    ASSERT_EQ(current.size(), 2);
    ASSERT_EQ(preEdit.size(), 2);

    EXPECT_EQ(current[0].getName(), "eDP-1");
    EXPECT_EQ(current[1].getName(), "DP-1");

    EXPECT_EQ(preEdit[0].getName(), "eDP-1");
    EXPECT_EQ(preEdit[1].getName(), "DP-1");
}

TEST(MonitorManagerTest, GetMonitorsReturnsReference) {
    TestableMonitorManager manager(nullptr);

    Monitor m;
    m.setName("DP-2");
    std::vector<Monitor> monitors = { m };
    manager.testSetMonitors(monitors);

    auto& ref1 = manager.getMonitors();
    auto& ref2 = manager.getMonitors();

    // They must be the same underlying object
    EXPECT_EQ(&ref1, &ref2);
}

TEST(MonitorManagerTest, GetPreUserEditMonitorsReturnsReference) {
    TestableMonitorManager manager(nullptr);

    Monitor m;
    m.setName("DP-2");
    std::vector<Monitor> monitors = { m };
    manager.testSetMonitors(monitors);

    auto& ref1 = manager.testGetPreUserEditMonitors();
    auto& ref2 = manager.testGetPreUserEditMonitors();

    EXPECT_EQ(&ref1, &ref2);
}
