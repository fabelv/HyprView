#include "hyprview_core/models/monitor.h"
#include "hyprview_core/utils/monitor_helpers.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <vector>

using namespace core;

TEST(AvailableMonitorTest, ThrowsOnEmptyMonitorList) {
  std::vector<Monitor> monitors{};
  Monitor m;

  EXPECT_THROW(
      { MonitorHelpers::getAvailableMirrorMonitors(m, monitors); },
      std::invalid_argument);
}

TEST(AvailableMonitorTest, AddsNoneAndOtherMonitorNamesWhenNotMirroring) {
  Monitor selected;
  selected.setName("HDMI-A-1");
  selected.setMirrorOf(""); // not mirroring

  Monitor other1;
  other1.setName("eDP-1");

  Monitor other2;
  other2.setName("DP-2");

  std::vector<Monitor> monitors{selected, other1, other2};

  auto result = MonitorHelpers::getAvailableMirrorMonitors(selected, monitors);

  // Should include "none", and names of other1 and other2
  EXPECT_EQ(result.size(), 3);
  EXPECT_EQ(result[0], "none");
  EXPECT_THAT(result, ::testing::ElementsAre("none", "eDP-1", "DP-2"));
}

TEST(AvailableMonitorTest, AddsOtherMonitorNamesAndNoneAtEndWhenMirroring) {
  Monitor selected;
  selected.setName("eDP-1");
  selected.setMirrorOf("HDMI-A-1"); // is currently mirroring

  Monitor other;
  other.setName("HDMI-A-1");

  std::vector<Monitor> monitors{selected, other};

  auto result = MonitorHelpers::getAvailableMirrorMonitors(selected, monitors);

  // Should contain only other monitor name and "none" (at the end)
  EXPECT_EQ(result.size(), 2);
  EXPECT_EQ(result[1], "none");
  EXPECT_THAT(result, ::testing::ElementsAre("HDMI-A-1", "none"));
}

TEST(AvailableMonitorTest, SkipsSelfFromAvailableList) {
  Monitor selected;
  selected.setName("DP-1");
  selected.setMirrorOf("");

  Monitor other1;
  other1.setName("DP-1"); // same name, should be skipped

  Monitor other2;
  other2.setName("DP-2");

  std::vector<Monitor> monitors{selected, other1, other2};

  auto result = MonitorHelpers::getAvailableMirrorMonitors(selected, monitors);

  EXPECT_THAT(result, ::testing::ElementsAre("none", "DP-2"));
}
