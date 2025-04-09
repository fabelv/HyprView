#include <gtest/gtest.h>
#include <hyprview_core/enums/transform.h>
#include <hyprview_core/models/monitor.h>

using namespace core;

TEST(MonitorTest, DefaultConstructor) {
  Monitor m;

  EXPECT_EQ(m.getId(), 0);
  EXPECT_EQ(m.getName(), "");
  EXPECT_EQ(m.getDescription(), "");
  EXPECT_EQ(m.getMake(), "");
  EXPECT_EQ(m.getModel(), "");
  EXPECT_EQ(m.getSerial(), "");
  EXPECT_EQ(m.getWidth(), 0);
  EXPECT_EQ(m.getHeight(), 0);
  EXPECT_DOUBLE_EQ(m.getRefreshRate(), 0.0);
  EXPECT_EQ(m.getPositionX(), 0);
  EXPECT_EQ(m.getPositionY(), 0);
  EXPECT_DOUBLE_EQ(m.getScale(), 0.0);
  EXPECT_EQ(m.getTransform(), Transform::Normal);
  EXPECT_FALSE(m.isFocused());
  EXPECT_FALSE(m.getDpmsStatus());
  EXPECT_FALSE(m.isVrrEnabled());
  EXPECT_EQ(m.getSolitary(), "");
  EXPECT_FALSE(m.isActivelyTearing());
  EXPECT_EQ(m.getDirectScanoutTo(), "");
  EXPECT_FALSE(m.isDisabled());
  EXPECT_EQ(m.getCurrentFormat(), "");
  EXPECT_EQ(m.getMirrorOf(), "");
  EXPECT_TRUE(m.getAvailableModes().empty());
}

TEST(MonitorTest, FullSetterGetterCoverage) {
  Monitor m;

  m.setId(42);
  m.setName("DP-1");
  m.setDescription("Main Display");
  m.setMake("ASUS");
  m.setModel("ROG Swift");
  m.setSerial("XYZ12345");
  m.setWidth(1920);
  m.setHeight(1080);
  m.setRefreshRate(165.0);
  m.setPositionX(100);
  m.setPositionY(200);
  m.setScale(1.5);
  m.setTransform(Transform::Flipped);
  m.setFocused(true);
  m.setDpmsStatus(true);
  m.setVrrEnabled(true);
  m.setSolitary("primary");
  m.setActivelyTearing(true);
  m.setDirectScanoutTo("eDP-1");
  m.setDisabled(true);
  m.setCurrentFormat("ARGB8888");
  m.setMirrorOf("HDMI-A-1");
  std::vector<std::string> modes = {"1920x1080@60Hz", "1280x720@60Hz"};
  m.setAvailableModes(modes);

  EXPECT_EQ(m.getId(), 42);
  EXPECT_EQ(m.getName(), "DP-1");
  EXPECT_EQ(m.getDescription(), "Main Display");
  EXPECT_EQ(m.getMake(), "ASUS");
  EXPECT_EQ(m.getModel(), "ROG Swift");
  EXPECT_EQ(m.getSerial(), "XYZ12345");
  EXPECT_EQ(m.getWidth(), 1920);
  EXPECT_EQ(m.getHeight(), 1080);
  EXPECT_DOUBLE_EQ(m.getRefreshRate(), 165.0);
  EXPECT_EQ(m.getPositionX(), 100);
  EXPECT_EQ(m.getPositionY(), 200);
  EXPECT_DOUBLE_EQ(m.getScale(), 1.5);
  EXPECT_EQ(m.getTransform(), Transform::Flipped);
  EXPECT_TRUE(m.isFocused());
  EXPECT_TRUE(m.getDpmsStatus());
  EXPECT_TRUE(m.isVrrEnabled());
  EXPECT_EQ(m.getSolitary(), "primary");
  EXPECT_TRUE(m.isActivelyTearing());
  EXPECT_EQ(m.getDirectScanoutTo(), "eDP-1");
  EXPECT_TRUE(m.isDisabled());
  EXPECT_EQ(m.getCurrentFormat(), "ARGB8888");
  EXPECT_EQ(m.getMirrorOf(), "HDMI-A-1");
  EXPECT_EQ(m.getAvailableModes(), modes);
}

TEST(MonitorTest, ToStringFormatsCorrectly) {
  Monitor m;
  m.setId(1);
  m.setName("DP-1");
  m.setWidth(1920);
  m.setHeight(1080);
  m.setRefreshRate(144.0);

  std::string expected = "Monitor[1] DP-1 (1920x1080 @ 144Hz)";
  EXPECT_EQ(m.toString(), expected);
}

TEST(MonitorTest, GenerateCurrentMode) {
  Monitor m;
  m.setWidth(2560);
  m.setHeight(1440);
  m.setRefreshRate(165.0);

  EXPECT_EQ(m.generateCurrentMode(), "2560x1440@165Hz");
}

TEST(MonitorTest, ApplyModeStringValid) {
  Monitor m;
  m.applyModeString("1920x1080@144Hz");

  EXPECT_EQ(m.getWidth(), 1920);
  EXPECT_EQ(m.getHeight(), 1080);
  EXPECT_DOUBLE_EQ(m.getRefreshRate(), 144.0);
}

TEST(MonitorTest, ApplyModeStringInvalidFormat) {
  Monitor m;
  m.setWidth(800);
  m.setHeight(600);
  m.setRefreshRate(60.0);

  m.applyModeString("not-a-valid-mode");

  // Should remain unchanged
  EXPECT_EQ(m.getWidth(), 800);
  EXPECT_EQ(m.getHeight(), 600);
  EXPECT_DOUBLE_EQ(m.getRefreshRate(), 60.0);
}

TEST(MonitorTest, CopyConstructor) {
  Monitor m;
  m.setName("Original");
  m.setWidth(1920);

  Monitor copy(m);

  EXPECT_EQ(copy.getName(), "Original");
  EXPECT_EQ(copy.getWidth(), 1920);
}

TEST(MonitorTest, CopyAssignment) {
  Monitor m1;
  m1.setName("First");
  m1.setHeight(1080);

  Monitor m2;
  m2 = m1;

  EXPECT_EQ(m2.getName(), "First");
  EXPECT_EQ(m2.getHeight(), 1080);
}
