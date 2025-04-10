#include <gtest/gtest.h>
#include <hyprview_core/parsers/hypr_monitor_parser.h>
#include <hyprview_core/models/monitor.h>

using namespace core;

TEST(HyprMonitorParserTest, ParsesMultipleMonitorsCorrectly) {
    const std::string json = R"([
        {
            "id": 0,
            "name": "DP-2",
            "description": "Ancor Communications Inc ROG PG348Q #ASO8/a/4npHd",
            "make": "Ancor Communications Inc",
            "model": "ROG PG348Q",
            "serial": "#ASO8/a/4npHd",
            "width": 3440,
            "height": 1440,
            "refreshRate": 59.97300,
            "x": 0,
            "y": 0,
            "scale": 1.00,
            "transform": 0,
            "focused": true,
            "dpmsStatus": true,
            "vrr": false,
            "solitary": "0",
            "activelyTearing": false,
            "directScanoutTo": "0",
            "disabled": false,
            "currentFormat": "XRGB8888",
            "mirrorOf": "none",
            "availableModes": ["3440x1440@59.97Hz","3440x1440@100.00Hz"]
        },
        {
            "id": 1,
            "name": "DP-4",
            "description": "BNQ BenQ GL2460 75D06515SL0",
            "make": "BNQ",
            "model": "BenQ GL2460",
            "serial": "75D06515SL0",
            "width": 1920,
            "height": 1080,
            "refreshRate": 60.00000,
            "x": 3440,
            "y": 0,
            "scale": 1.00,
            "transform": 0,
            "focused": false,
            "dpmsStatus": true,
            "vrr": false,
            "solitary": "0",
            "activelyTearing": false,
            "directScanoutTo": "0",
            "disabled": false,
            "currentFormat": "XRGB8888",
            "mirrorOf": "none",
            "availableModes": ["1920x1080@60.00Hz","1920x1080@59.94Hz"]
        }
    ])";

    HyprMonitorParser parser;
    std::vector<Monitor> monitors = parser.parseMonitorsFromJson(json);

    ASSERT_EQ(monitors.size(), 2);

    const Monitor& m1 = monitors[0];
    EXPECT_EQ(m1.getId(), 0);
    EXPECT_EQ(m1.getName(), "DP-2");
    EXPECT_EQ(m1.getDescription(), "Ancor Communications Inc ROG PG348Q #ASO8/a/4npHd");
    EXPECT_EQ(m1.getMake(), "Ancor Communications Inc");
    EXPECT_EQ(m1.getModel(), "ROG PG348Q");
    EXPECT_EQ(m1.getSerial(), "#ASO8/a/4npHd");
    EXPECT_EQ(m1.getWidth(), 3440);
    EXPECT_EQ(m1.getHeight(), 1440);
    EXPECT_DOUBLE_EQ(m1.getRefreshRate(), 59.97);
    EXPECT_EQ(m1.getPositionX(), 0);
    EXPECT_EQ(m1.getPositionY(), 0);
    EXPECT_DOUBLE_EQ(m1.getScale(), 1.0);
    EXPECT_EQ(m1.getTransform(), Transform::Normal);
    EXPECT_TRUE(m1.getDpmsStatus());
    EXPECT_FALSE(m1.isVrrEnabled());
    EXPECT_EQ(m1.getSolitary(), "0");
    EXPECT_FALSE(m1.isActivelyTearing());
    EXPECT_EQ(m1.getDirectScanoutTo(), "0");
    EXPECT_FALSE(m1.isDisabled());
    EXPECT_EQ(m1.getCurrentFormat(), "XRGB8888");
    EXPECT_EQ(m1.getMirrorOf(), "none");
    EXPECT_EQ(m1.getAvailableModes().size(), 2);
    EXPECT_EQ(m1.getAvailableModes()[0], "3440x1440@59.97Hz");

    const Monitor& m2 = monitors[1];
    EXPECT_EQ(m2.getId(), 1);
    EXPECT_EQ(m2.getName(), "DP-4");
    EXPECT_EQ(m2.getDescription(), "BNQ BenQ GL2460 75D06515SL0");
    EXPECT_EQ(m2.getMake(), "BNQ");
    EXPECT_EQ(m2.getModel(), "BenQ GL2460");
    EXPECT_EQ(m2.getSerial(), "75D06515SL0");
    EXPECT_EQ(m2.getWidth(), 1920);
    EXPECT_EQ(m2.getHeight(), 1080);
    EXPECT_DOUBLE_EQ(m2.getRefreshRate(), 60.00);
    EXPECT_EQ(m2.getPositionX(), 3440);
    EXPECT_EQ(m2.getPositionY(), 0);
    EXPECT_DOUBLE_EQ(m2.getScale(), 1.0);
    EXPECT_EQ(m2.getTransform(), Transform::Normal);
    EXPECT_TRUE(m2.getDpmsStatus());
    EXPECT_FALSE(m2.isVrrEnabled());
    EXPECT_EQ(m2.getSolitary(), "0");
    EXPECT_FALSE(m2.isActivelyTearing());
    EXPECT_EQ(m2.getDirectScanoutTo(), "0");
    EXPECT_FALSE(m2.isDisabled());
    EXPECT_EQ(m2.getCurrentFormat(), "XRGB8888");
    EXPECT_EQ(m2.getMirrorOf(), "none");
    EXPECT_EQ(m2.getAvailableModes().size(), 2);
    EXPECT_EQ(m2.getAvailableModes()[1], "1920x1080@59.94Hz");
}
