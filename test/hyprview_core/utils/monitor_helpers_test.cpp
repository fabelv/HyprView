#include "hyprview_core/models/monitor.h"
#include "hyprview_core/utils/logger.h"
#include "hyprview_core/utils/monitor_helpers.h"
#include <gtest/gtest.h>
#include <string>
#include <vector>

using namespace core;

TEST(MonitorHelpersTest, getAvailableMirrorMonitors){
    Monitor m1;
    Monitor m2;

    m1.setName("DP-1");
    m2.setName("DP-2");

    std::vector<Monitor> monitors;
    monitors.push_back(m1);
    monitors.push_back(m2);

    auto result = MonitorHelpers::getAvailableMirrorMonitors(m1, monitors);

    EXPECT_EQ(result.size(), 2);
    EXPECT_EQ(result.at(0), "none");
    EXPECT_EQ(result.at(1), "DP-2");
}

TEST(MonitorHelpersTest, getAvailableMirrorMonitorsMirrorPresent){
    Monitor m1;
    Monitor m2;

    m1.setName("DP-1");
    m1.setMirrorOf("DP-2");
    m2.setName("DP-2");

    std::vector<Monitor> monitors;
    monitors.push_back(m1);
    monitors.push_back(m2);

    auto result = MonitorHelpers::getAvailableMirrorMonitors(m1, monitors);

    EXPECT_EQ(result.size(), 2);
    EXPECT_EQ(result.at(0), "DP-2");
    EXPECT_EQ(result.at(1), "none");
}

