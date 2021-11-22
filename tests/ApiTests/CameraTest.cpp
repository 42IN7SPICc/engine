#include <gtest/gtest.h>
#include "Camera.hpp"
#include "Color.hpp"

spic::Camera camera {"camera", (int) 1, spic::Color::black(), 0, 0};

TEST(CameraTest, TestAspectWidthProperty) {
    camera.AspectWidth(100);
    ASSERT_EQ(100, camera.AspectWidth());
}

TEST(CameraTest, TestAspectHeightProperty) {
    camera.AspectWidth(67);
    ASSERT_EQ(67, camera.AspectWidth());
}