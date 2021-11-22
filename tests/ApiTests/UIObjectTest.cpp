#include <gtest/gtest.h>
#include "UIObject.hpp"

spic::UIObject uiObject {"bar", "ui", 1, 0, 0};

TEST(UIObjectTest, TestWidthProperty) {
    uiObject.Width(144);
    ASSERT_EQ(144, uiObject.Width());
}

TEST(UIObjectTest, TestHeightProperty) {
    uiObject.Height(62);
    ASSERT_EQ(62, uiObject.Height());
}