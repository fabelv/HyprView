#include <gtest/gtest.h>
#include "hyprview_core/parsers/hypr_monitor_parser.h"

using namespace core;


auto runParse(const std::string& json) -> std::vector<Monitor> {
    HyprMonitorParser parser;
    return parser.parseMonitorsFromJson(json);
}

TEST(HyprMonitorParserTest, ParsesSingleMonitorCorrectly) {
    const std::string json = R"([
        {
            "id": 1,
            "name": "DP-1",
            "description": "Test Monitor",
            "make": "TestMake",
            "model": "TestModel",
            "serial": "123ABC",
            "width": 1920,
            "height": 1080,
            "refreshRate": 60.0,
            "x": 0,
            "y": 0,
            "scale": 1.0,
            "transform": 0,
            "dpmsStatus": true,
            "vrr": false,
            "solitary": "0",
            "activelyTearing": false,
            "directScanoutTo": "0",
            "disabled": false,
            "currentFormat": "XRGB8888",
            "mirrorOf": "none",
            "availableModes": ["1920x1080@60.00Hz"]
        }
    ])";

    auto monitors = runParse(json);
    ASSERT_EQ(monitors.size(), 1);
    const auto& m = monitors[0];
    EXPECT_EQ(m.getId(), 1);
    EXPECT_EQ(m.getName(), "DP-1");
    EXPECT_EQ(m.getDescription(), "Test Monitor");
    EXPECT_EQ(m.getMake(), "TestMake");
    EXPECT_EQ(m.getModel(), "TestModel");
    EXPECT_EQ(m.getSerial(), "123ABC");
    EXPECT_EQ(m.getWidth(), 1920);
    EXPECT_EQ(m.getHeight(), 1080);
    EXPECT_DOUBLE_EQ(m.getRefreshRate(), 60.0);
    EXPECT_EQ(m.getPositionX(), 0);
    EXPECT_EQ(m.getPositionY(), 0);
    EXPECT_DOUBLE_EQ(m.getScale(), 1.0);
    EXPECT_EQ(m.getTransform(), Transform::Normal);
    EXPECT_TRUE(m.getDpmsStatus());
    EXPECT_FALSE(m.getVrrEnabled());
    EXPECT_EQ(m.getSolitary(), "0");
    EXPECT_FALSE(m.getActivelyTearing());
    EXPECT_EQ(m.getDirectScanoutTo(), "0");
    EXPECT_FALSE(m.getDisabled());
    EXPECT_EQ(m.getCurrentFormat(), "XRGB8888");
    EXPECT_EQ(m.getMirrorOf(), "none");
    ASSERT_EQ(m.getAvailableModes().size(), 1);
    EXPECT_EQ(m.getAvailableModes()[0], "1920x1080@60.00Hz");
}

TEST(HyprMonitorParserTest, ParsesMultipleMonitorsCorrectly) {
    const std::string json = R"([
        {
            "id": 0,
            "name": "DP-2",
            "description": "Monitor A",
            "make": "MakerA",
            "model": "ModelA",
            "serial": "A123",
            "width": 3440,
            "height": 1440,
            "refreshRate": 59.97,
            "x": 0,
            "y": 0,
            "scale": 1.0,
            "transform": 0,
            "dpmsStatus": true,
            "vrr": false,
            "solitary": "0",
            "activelyTearing": false,
            "directScanoutTo": "0",
            "disabled": false,
            "currentFormat": "XRGB8888",
            "mirrorOf": "none",
            "availableModes": ["3440x1440@59.97Hz"]
        },
        {
            "id": 1,
            "name": "DP-4",
            "description": "Monitor B",
            "make": "MakerB",
            "model": "ModelB",
            "serial": "B456",
            "width": 1920,
            "height": 1080,
            "refreshRate": 60.0,
            "x": 3440,
            "y": 0,
            "scale": 1.0,
            "transform": 0,
            "dpmsStatus": true,
            "vrr": false,
            "solitary": "0",
            "activelyTearing": false,
            "directScanoutTo": "0",
            "disabled": false,
            "currentFormat": "XRGB8888",
            "mirrorOf": "none",
            "availableModes": ["1920x1080@60.00Hz"]
        }
    ])";

    auto monitors = runParse(json);
    ASSERT_EQ(monitors.size(), 2);
    EXPECT_EQ(monitors[0].getName(), "DP-2");
    EXPECT_EQ(monitors[1].getName(), "DP-4");
}

TEST(HyprMonitorParserTest, FailsWhenJsonIsNotArray) {
    const std::string json = R"(
        { "id": 0, "name": "DP-1" }
    )";

    auto monitors = runParse(json);
    EXPECT_TRUE(monitors.empty());
}

TEST(HyprMonitorParserTest, FailsOnMalformedJson) {
    const std::string json = R"([
        { "id": 1, "name": "DP-1", }
    ])"; // trailing comma

    auto monitors = runParse(json);
    EXPECT_TRUE(monitors.empty());
}

TEST(HyprMonitorParserTest, FailsWhenMonitorMissingRequiredField) {
    const std::string json = R"([
        {
            "id": 1,
            "width": 1920,
            "height": 1080
        }
    ])";

    auto monitors = runParse(json);
    EXPECT_TRUE(monitors.empty());
}

TEST(HyprMonitorParserTest, ParsesEmptyArray) {
    const std::string json = R"([])";
    auto monitors = runParse(json);
    EXPECT_TRUE(monitors.empty());
}

TEST(HyprMonitorParserTest, IgnoresPartialInvalidMonitor) {
    const std::string json = R"([
        {
            "id": 0,
            "name": "DP-1",
            "description": "Valid",
            "make": "Make",
            "model": "Model",
            "serial": "Serial",
            "width": 1920,
            "height": 1080,
            "refreshRate": 60.0,
            "x": 0,
            "y": 0,
            "scale": 1.0,
            "transform": 0,
            "dpmsStatus": true,
            "vrr": false,
            "solitary": "0",
            "activelyTearing": false,
            "directScanoutTo": "0",
            "disabled": false,
            "currentFormat": "XRGB8888",
            "mirrorOf": "none",
            "availableModes": ["1920x1080@60.00Hz"]
        },
        {
            "id": 1
            // invalid: missing all other fields
        }
    ])";

    auto monitors = runParse(json);
    EXPECT_TRUE(monitors.empty());
}

