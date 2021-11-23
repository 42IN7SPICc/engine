#include <gtest/gtest.h>
#include "Point.hpp"
#include "../../src/Utils/ZoneUtil.hpp"



TEST(ZoneUtilTest, TestInZoneMethod)
{
    spic::Point point {10,10};
    std::vector<spic::Point> points {
        spic::Point {0,0},
        spic::Point {20,0},
        spic::Point {20,20},
        spic::Point {0,20}
    };
    bool inZone = engine::ZoneUtil::InZone(point, points);
    ASSERT_TRUE(inZone);
}

TEST(ZoneUtilTest, TestOutsideZoneMethod)
{
    spic::Point point {25,25};
    std::vector<spic::Point> points {
            spic::Point {0,0},
            spic::Point {20,0},
            spic::Point {20,20},
            spic::Point {0,20}
    };
    bool outsideZone = engine::ZoneUtil::InZone(point, points);
    ASSERT_FALSE(outsideZone);
}


TEST(ZoneUtilTest, TestGetCenterMethod)
{
    std::vector<spic::Point> points {
            spic::Point {0,0},
            spic::Point {20,0},
            spic::Point {20,20},
            spic::Point {0,20}
    };
    spic::Point center = engine::ZoneUtil::GetCenter(points);
    ASSERT_EQ(center.x, 10);
    ASSERT_EQ(center.y, 10);
}