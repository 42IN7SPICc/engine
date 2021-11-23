#include <gtest/gtest.h>
#include "Point.hpp"
#include "../../src/Utils/RectangleUtil.hpp"

spic::Point center{200, 200};
int width = 100;
int height = 50;

TEST(RectangleUtilTest, testRotateMethod)
{
    auto points = engine::RectangleUtil::Rotate(center, width, height, 0);
    ASSERT_EQ(points[0].x, 150);
    ASSERT_EQ(points[0].y, 225);

    ASSERT_EQ(points[1].x, 250);
    ASSERT_EQ(points[1].y, 225);

    ASSERT_EQ(points[2].x, 250);
    ASSERT_EQ(points[2].y, 175);

    ASSERT_EQ(points[3].x, 150);
    ASSERT_EQ(points[3].y, 175);
}