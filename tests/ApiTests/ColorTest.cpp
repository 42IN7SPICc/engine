#include <gtest/gtest.h>
#include "Color.hpp"

spic::Color color {1.0,1.0, 1.0, 1.0};

TEST(ColorTest, TestSetColorProperties) {
    color.SetColor(0.5, 0.2, 0.3);
    ASSERT_EQ(0.5, color.R());
    ASSERT_EQ(0.2, color.G());
    ASSERT_EQ(0.3, color.B());
}

TEST(ColorTest, TestWhiteColor) {
    color = spic::Color::white();
    ASSERT_EQ(1.0, color.R());
    ASSERT_EQ(1.0, color.G());
    ASSERT_EQ(1.0, color.B());
    ASSERT_EQ(1.0, color.A());
}

TEST(ColorTest, TestRedColor) {
    color = spic::Color::red();
    ASSERT_EQ(1.0, color.R());
    ASSERT_EQ(0.0, color.G());
    ASSERT_EQ(0.0, color.B());
    ASSERT_EQ(1.0, color.A());
}

TEST(ColorTest, TestGreenColor) {
    color = spic::Color::green();
    ASSERT_EQ(0.0, color.R());
    ASSERT_EQ(1.0, color.G());
    ASSERT_EQ(0.0, color.B());
    ASSERT_EQ(1.0, color.A());
}

TEST(ColorTest, TestBlueColor) {
    color = spic::Color::blue();
    ASSERT_EQ(0.0, color.R());
    ASSERT_EQ(0.0, color.G());
    ASSERT_EQ(1.0, color.B());
    ASSERT_EQ(1.0, color.A());
}

TEST(ColorTest, TestCyanColor) {
    color = spic::Color::cyan();
    ASSERT_EQ(0.0, color.R());
    ASSERT_EQ(1.0, color.G());
    ASSERT_EQ(1.0, color.B());
    ASSERT_EQ(1.0, color.A());
}

TEST(ColorTest, TestMagentaColor) {
    color = spic::Color::magenta();
    ASSERT_EQ(1.0, color.R());
    ASSERT_EQ(0.0, color.G());
    ASSERT_EQ(1.0, color.B());
    ASSERT_EQ(1.0, color.A());
}

TEST(ColorTest, TestYellowColor) {
    color = spic::Color::yellow();
    ASSERT_EQ(1.0, color.R());
    ASSERT_EQ(1.0, color.G());
    ASSERT_EQ(0.0, color.B());
    ASSERT_EQ(1.0, color.A());
}

TEST(ColorTest, TestBlackColor) {
    color = spic::Color::black();
    ASSERT_EQ(0.0, color.R());
    ASSERT_EQ(0.0, color.G());
    ASSERT_EQ(0.0, color.B());
    ASSERT_EQ(1.0, color.A());
}

TEST(ColorTest, TestPurpleColor) {
    color = spic::Color::purple();
    ASSERT_EQ(0.5, color.R());
    ASSERT_EQ(0.0, color.G());
    ASSERT_EQ(0.5, color.B());
    ASSERT_EQ(1.0, color.A());
}

TEST(ColorTest, TestLimeColor) {
    color = spic::Color::lime();
    ASSERT_EQ(0.75, color.R());
    ASSERT_EQ(1.0, color.G());
    ASSERT_EQ(0.0, color.B());
    ASSERT_EQ(1.0, color.A());
}

TEST(ColorTest, TestOrangeColor) {
    color = spic::Color::orange();
    ASSERT_EQ(1.0, color.R());
    ASSERT_EQ(0.6, color.G());
    ASSERT_EQ(0.0, color.B());
    ASSERT_EQ(1.0, color.A());
}

TEST(ColorTest, TestTransparantColor) {
    color = spic::Color::transparent();
    ASSERT_EQ(0.0, color.R());
    ASSERT_EQ(0.0, color.G());
    ASSERT_EQ(0.0, color.B());
    ASSERT_EQ(0.0, color.A());
}