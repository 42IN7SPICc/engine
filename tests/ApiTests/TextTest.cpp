#include <gtest/gtest.h>
#include "Text.hpp"

spic::Text text{"testText", "text_tag", 0, 0, 0};

TEST(TextTest, TestContentProperty)
{
    text.Content("hello world");
    ASSERT_EQ("hello world", text.Content());
}

TEST(TextTest, TestFontProperty)
{
    text.Font("test.ttf");
    ASSERT_EQ("test.ttf", text.Font());
}

TEST(TextTest, TestAllignmentProperty)
{
    text.TextAlignment(spic::Alignment::center);
    ASSERT_EQ(spic::Alignment::center, text.TextAlignment());
}

TEST(TextTest, TestSizeProperty)
{
    text.Size(24);
    ASSERT_EQ(24, text.Size());
}

TEST(TextTest, TestTextColortProperty)
{
    text.TextColor(spic::Color::green());
    ASSERT_EQ(0.0, text.TextColor().R());
    ASSERT_EQ(1.0, text.TextColor().G());
    ASSERT_EQ(0.0, text.TextColor().B());
}