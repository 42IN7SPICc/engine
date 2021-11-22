#include <gtest/gtest.h>
#include "BoxCollider.hpp"

spic::BoxCollider boxCollider {0, 0};

TEST(BoxColliderTest, TestWidthProperty) {
    boxCollider.Width(10.5);
    ASSERT_EQ(10.5, boxCollider.Width());
}

TEST(BoxColliderTest, TestHeightProperty) {
    boxCollider.Height(52.8);
    ASSERT_EQ(52.8, boxCollider.Height());
}


TEST(BoxColliderTest, TestIsTriggerProperty) {
    boxCollider.IsTrigger(true);
    ASSERT_EQ(true, boxCollider.IsTrigger());
}