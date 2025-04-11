#include <gtest/gtest.h>
#include <hyprview_core/models/monitor.h>
#include <hyprview_core/utils/monitor_geometry.h>

using namespace core;

Monitor makeMonitor(int x, int y, int width, int height) {
  Monitor m;
  m.setPositionX(x);
  m.setPositionY(y);
  m.setWidth(width);
  m.setHeight(height);
  return m;
}

TEST(MonitorGeometryTest, SnapReturnsOriginalIfAlone) {
  Monitor m = makeMonitor(0, 0, 1920, 1080);
  std::vector<Monitor> all = {m};

  Position result = MonitorGeometry::getSnappedPosition(m, all);

  EXPECT_EQ(result.x, 0);
  EXPECT_EQ(result.y, 0);
}

TEST(MonitorGeometryTest, SnapsToRightSide) {
  Monitor left = makeMonitor(0, 0, 1920, 1080);
  Monitor right = makeMonitor(1925, 0, 1920, 1080); // Close but not snapped
  std::vector<Monitor> monitors = {left, right};

  // Move right monitor slightly left so it "snaps" to the left's right edge
  right.setPositionX(1920 - 5);

  Position snapped = MonitorGeometry::getSnappedPosition(right, monitors);

  // Expect right's left edge to be aligned with left's right edge (1920)
  EXPECT_EQ(snapped.x, 1920);
  EXPECT_EQ(snapped.y, 0);
}

TEST(MonitorGeometryCornerSnapTest, SnapsToTopLeftCorner) {
  Monitor dragged = makeMonitor(120, 120, 100, 100); // bottom-right of target
  Monitor target = makeMonitor(0, 0, 100, 100);

  std::vector<Monitor> monitors = {target, dragged};

  Position result = MonitorGeometry::getSnappedPosition(dragged, monitors);

  EXPECT_EQ(result.x, 100); // snapped to right of target
  EXPECT_EQ(result.y, 100); // snapped to bottom of target
}

TEST(MonitorGeometryCornerSnapTest, SnapsToBottomRightCorner) {
  Monitor dragged =
      makeMonitor(-90, -90, 100, 100);            // slightly off from (10,10)
  Monitor target = makeMonitor(10, 10, 100, 100); // top-left is at (10,10)

  std::vector<Monitor> monitors = {target, dragged};

  Position result = MonitorGeometry::getSnappedPosition(dragged, monitors);

  EXPECT_EQ(result.x, -90);
  EXPECT_EQ(result.y, -90);
}

TEST(MonitorGeometryCornerSnapTest, SnapsToTopRightCorner) {
  Monitor dragged =
      makeMonitor(-90, 90, 100, 100);              // slightly off from (10,100)
  Monitor target = makeMonitor(10, 100, 100, 100); // top-left is at (10,100)

  std::vector<Monitor> monitors = {target, dragged};

  Position result = MonitorGeometry::getSnappedPosition(dragged, monitors);

  EXPECT_EQ(result.x, -90);
  EXPECT_EQ(result.y, 90);
}

TEST(MonitorGeometryTest, SnapsToBottomSide) {
  Monitor top = makeMonitor(0, 0, 1920, 1080);
  Monitor bottom = makeMonitor(0, 1085, 1920, 1080);
  bottom.setPositionY(1080 - 10); // close enough to snap

  std::vector<Monitor> monitors = {top, bottom};

  Position snapped = MonitorGeometry::getSnappedPosition(bottom, monitors);

  EXPECT_EQ(snapped.x, 0);
  EXPECT_EQ(snapped.y, 1080); // aligned below top
}

TEST(MonitorGeometryTest, CalculatesPreviewScaleFactor) {
  Monitor m1 = makeMonitor(0, 0, 1920, 1080);
  Monitor m2 = makeMonitor(1920, 0, 1920, 1080);
  std::vector<Monitor> monitors = {m1, m2};

  int previewWidth = 1000;
  int previewHeight = 500;
  float margin = 0.9F;

  double scale = MonitorGeometry::calculatePreviewScaleFactor(
      previewWidth, previewHeight, margin, monitors);

  // Total width = 3840, height = 1080 → expect scale to fit within 900x450
  EXPECT_GT(scale, 0.0);
  EXPECT_LT(scale, 1.0);
}

TEST(MonitorGeometryTest, CalculatesCenteredOffsetCorrectly) {
  Monitor m1 = makeMonitor(0, 0, 1920, 1080);
  Monitor m2 = makeMonitor(1920, 0, 1920, 1080);
  std::vector<Monitor> monitors = {m1, m2};

  int areaWidth = 2000;
  int areaHeight = 1500;
  double scale = 0.2;

  Position offset = MonitorGeometry::calculateCenteredOffset(
      monitors, scale, areaWidth, areaHeight);

  int expectedContentWidth = static_cast<int>((1920 + 1920) * scale);
  int expectedContentHeight = static_cast<int>(1080 * scale);

  EXPECT_EQ(offset.x, (areaWidth - expectedContentWidth) / 2);
  EXPECT_EQ(offset.y, (areaHeight - expectedContentHeight) / 2);
}
