#include <gtest/gtest.h>
#include <hyprview_core/enums/transform.h>
#include <hyprview_core/models/monitor.h>

using namespace core;

// constructors

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
  EXPECT_FALSE(m.getDpmsStatus());
  EXPECT_FALSE(m.getVrrEnabled());
  EXPECT_EQ(m.getSolitary(), "");
  EXPECT_FALSE(m.getActivelyTearing());
  EXPECT_EQ(m.getDirectScanoutTo(), "");
  EXPECT_FALSE(m.getDisabled());
  EXPECT_EQ(m.getCurrentFormat(), "");
  EXPECT_EQ(m.getMirrorOf(), "");
  EXPECT_TRUE(m.getAvailableModes().empty());
}

TEST(MonitorTest, CopyConstructorDeepCopy) {
  Monitor m;
  m.setId(1);
  m.setName("eDP-1");
  m.setDescription("Built-in Display");
  m.setMake("Dell");
  m.setModel("XPS");
  m.setSerial("ABC123");
  m.setWidth(1920);
  m.setHeight(1080);
  m.setRefreshRate(60.0);
  m.setPositionX(0);
  m.setPositionY(0);
  m.setScale(1.0);
  m.setTransform(Transform::Normal);
  m.setDpmsStatus(true);
  m.setVrrEnabled(false);
  m.setSolitary("yes");
  m.setActivelyTearing(false);
  m.setDirectScanoutTo("none");
  m.setDisabled(false);
  m.setCurrentFormat("XRGB8888");
  m.setMirrorOf("HDMI-A-1");
  m.setAvailableModes({"1920x1080@60Hz", "1280x720@60Hz"});

  Monitor copy(m);

  // Check all fields are equal
  EXPECT_EQ(copy.getId(), m.getId());
  EXPECT_EQ(copy.getName(), m.getName());
  EXPECT_EQ(copy.getDescription(), m.getDescription());
  EXPECT_EQ(copy.getMake(), m.getMake());
  EXPECT_EQ(copy.getModel(), m.getModel());
  EXPECT_EQ(copy.getSerial(), m.getSerial());
  EXPECT_EQ(copy.getWidth(), m.getWidth());
  EXPECT_EQ(copy.getHeight(), m.getHeight());
  EXPECT_DOUBLE_EQ(copy.getRefreshRate(), m.getRefreshRate());
  EXPECT_EQ(copy.getPositionX(), m.getPositionX());
  EXPECT_EQ(copy.getPositionY(), m.getPositionY());
  EXPECT_DOUBLE_EQ(copy.getScale(), m.getScale());
  EXPECT_EQ(copy.getTransform(), m.getTransform());
  EXPECT_EQ(copy.getDpmsStatus(), m.getDpmsStatus());
  EXPECT_EQ(copy.getVrrEnabled(), m.getVrrEnabled());
  EXPECT_EQ(copy.getSolitary(), m.getSolitary());
  EXPECT_EQ(copy.getActivelyTearing(), m.getActivelyTearing());
  EXPECT_EQ(copy.getDirectScanoutTo(), m.getDirectScanoutTo());
  EXPECT_EQ(copy.getDisabled(), m.getDisabled());
  EXPECT_EQ(copy.getCurrentFormat(), m.getCurrentFormat());
  EXPECT_EQ(copy.getMirrorOf(), m.getMirrorOf());
  EXPECT_EQ(copy.getAvailableModes(), m.getAvailableModes());

  // Mutate original and make sure copy is unaffected
  m.setAvailableModes({"800x600@60Hz"});
  EXPECT_NE(copy.getAvailableModes(), m.getAvailableModes());
}

// operators

TEST(MonitorTest, CopyAssignmentDeepCopy) {
  Monitor m1;
  m1.setId(7);
  m1.setName("HDMI-A-2");
  m1.setDescription("External Monitor");
  m1.setMake("LG");
  m1.setModel("Ultrafine");
  m1.setSerial("LG9876");
  m1.setWidth(3840);
  m1.setHeight(2160);
  m1.setRefreshRate(120.0);
  m1.setPositionX(1920);
  m1.setPositionY(0);
  m1.setScale(1.25);
  m1.setTransform(Transform::Flipped);
  m1.setDpmsStatus(false);
  m1.setVrrEnabled(true);
  m1.setSolitary("no");
  m1.setActivelyTearing(true);
  m1.setDirectScanoutTo("eDP-1");
  m1.setDisabled(true);
  m1.setCurrentFormat("RGBA8888");
  m1.setMirrorOf("none");
  m1.setAvailableModes({"3840x2160@120Hz", "2560x1440@60Hz"});

  Monitor m2;
  m2 = m1;

  // Check all fields copied
  EXPECT_EQ(m2.getId(), m1.getId());
  EXPECT_EQ(m2.getName(), m1.getName());
  EXPECT_EQ(m2.getDescription(), m1.getDescription());
  EXPECT_EQ(m2.getMake(), m1.getMake());
  EXPECT_EQ(m2.getModel(), m1.getModel());
  EXPECT_EQ(m2.getSerial(), m1.getSerial());
  EXPECT_EQ(m2.getWidth(), m1.getWidth());
  EXPECT_EQ(m2.getHeight(), m1.getHeight());
  EXPECT_DOUBLE_EQ(m2.getRefreshRate(), m1.getRefreshRate());
  EXPECT_EQ(m2.getPositionX(), m1.getPositionX());
  EXPECT_EQ(m2.getPositionY(), m1.getPositionY());
  EXPECT_DOUBLE_EQ(m2.getScale(), m1.getScale());
  EXPECT_EQ(m2.getTransform(), m1.getTransform());
  EXPECT_EQ(m2.getDpmsStatus(), m1.getDpmsStatus());
  EXPECT_EQ(m2.getVrrEnabled(), m1.getVrrEnabled());
  EXPECT_EQ(m2.getSolitary(), m1.getSolitary());
  EXPECT_EQ(m2.getActivelyTearing(), m1.getActivelyTearing());
  EXPECT_EQ(m2.getDirectScanoutTo(), m1.getDirectScanoutTo());
  EXPECT_EQ(m2.getDisabled(), m1.getDisabled());
  EXPECT_EQ(m2.getCurrentFormat(), m1.getCurrentFormat());
  EXPECT_EQ(m2.getMirrorOf(), m1.getMirrorOf());
  EXPECT_EQ(m2.getAvailableModes(), m1.getAvailableModes());

  // Mutate original and make sure copy is unaffected
  m1.setAvailableModes({"1024x768@60Hz"});
  EXPECT_NE(m2.getAvailableModes(), m1.getAvailableModes());
}

// core methods

TEST(MonitorTest, ApplyModeStringValid1) {
  Monitor m;
  m.applyModeString("1920x1080@144Hz");

  EXPECT_EQ(m.getWidth(), 1920);
  EXPECT_EQ(m.getHeight(), 1080);
  EXPECT_DOUBLE_EQ(m.getRefreshRate(), 144);
}

TEST(MonitorTest, ApplyModeStringValid2) {
  Monitor m;
  m.applyModeString("1920x1080@144.2Hz");

  EXPECT_EQ(m.getWidth(), 1920);
  EXPECT_EQ(m.getHeight(), 1080);
  EXPECT_DOUBLE_EQ(m.getRefreshRate(), 144.2);
}

TEST(MonitorTest, ApplyModeStringMultipleCalls) {
  Monitor m;
  m.applyModeString("1024x768@60Hz");
  EXPECT_EQ(m.getWidth(), 1024);
  EXPECT_EQ(m.getHeight(), 768);
  EXPECT_DOUBLE_EQ(m.getRefreshRate(), 60.0);

  m.applyModeString("1920x1080@144Hz");
  EXPECT_EQ(m.getWidth(), 1920);
  EXPECT_EQ(m.getHeight(), 1080);
  EXPECT_DOUBLE_EQ(m.getRefreshRate(), 144.0);
}

TEST(MonitorTest, ApplyModeStringHighPrecisionRefreshRate) {
  Monitor m;
  m.applyModeString("1920x1080@144.123456Hz");

  EXPECT_DOUBLE_EQ(m.getRefreshRate(), 144.123456);
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

TEST(MonitorTest, ApplyModeStringPartlyValidFormat1) {
  Monitor m;
  m.setWidth(800);
  m.setHeight(600);
  m.setRefreshRate(60.0);

  m.applyModeString("testx1080@144Hz");

  // Should remain unchanged
  EXPECT_EQ(m.getWidth(), 800);
  EXPECT_EQ(m.getHeight(), 600);
  EXPECT_DOUBLE_EQ(m.getRefreshRate(), 60.0);
}

TEST(MonitorTest, ApplyModeStringPartlyValidFormat2) {
  Monitor m;
  m.setWidth(800);
  m.setHeight(600);
  m.setRefreshRate(60.0);

  m.applyModeString("1920xtest@144Hz");

  // Should remain unchanged
  EXPECT_EQ(m.getWidth(), 800);
  EXPECT_EQ(m.getHeight(), 600);
  EXPECT_DOUBLE_EQ(m.getRefreshRate(), 60.0);
}

TEST(MonitorTest, ApplyModeStringPartlyValidFormat3) {
  Monitor m;
  m.setWidth(800);
  m.setHeight(600);
  m.setRefreshRate(60.0);

  m.applyModeString("1920x1080@testHz");

  // Should remain unchanged
  EXPECT_EQ(m.getWidth(), 800);
  EXPECT_EQ(m.getHeight(), 600);
  EXPECT_DOUBLE_EQ(m.getRefreshRate(), 60.0);
}

TEST(MonitorTest, GenerateCurrentModeDefault) {
  Monitor m;

  EXPECT_EQ(m.generateCurrentMode(), "0x0@0Hz");
}

TEST(MonitorTest, GenerateCurrentMode) {
  Monitor m;
  m.setWidth(2560);
  m.setHeight(1440);
  m.setRefreshRate(165.0);

  EXPECT_EQ(m.generateCurrentMode(), "2560x1440@165Hz");
}

// accessors

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
  EXPECT_TRUE(m.getDpmsStatus());
  EXPECT_TRUE(m.getVrrEnabled());
  EXPECT_EQ(m.getSolitary(), "primary");
  EXPECT_TRUE(m.getActivelyTearing());
  EXPECT_EQ(m.getDirectScanoutTo(), "eDP-1");
  EXPECT_TRUE(m.getDisabled());
  EXPECT_EQ(m.getCurrentFormat(), "ARGB8888");
  EXPECT_EQ(m.getMirrorOf(), "HDMI-A-1");
  EXPECT_EQ(m.getAvailableModes(), modes);
}
