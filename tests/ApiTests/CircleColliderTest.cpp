#include <gtest/gtest.h>
#include "CircleCollider.hpp"

spic::CircleCollider circleCollider{0};

TEST(CircleColliderTest, TestRadiusProperty)
{
    circleCollider.Radius(100);
    ASSERT_EQ(100, circleCollider.Radius());
}

TEST(CircleColliderTest, TestIsTriggerProperty)
{
    circleCollider.IsTrigger(true);
    ASSERT_TRUE(circleCollider.IsTrigger());
}