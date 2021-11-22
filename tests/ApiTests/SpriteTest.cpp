#include <gtest/gtest.h>
#include "Sprite.hpp"

spic::Sprite sprite {"https://media.istockphoto.com/photos/profile-of-a-toucan-picture-id139677202", spic::Color::blue(), false, false, 1, 1};

TEST(SpriteTest, CheckTextureProperty) {
    sprite.Texture("newTestTexture");
    ASSERT_EQ("newTestTexture", sprite.Texture());
}

TEST(SpriteTest, CheckColorProperty) {
    sprite.Color(spic::Color::black());
    ASSERT_EQ(0.0, sprite.Color().R());
    ASSERT_EQ(0.0, sprite.Color().G());
    ASSERT_EQ(0.0 , sprite.Color().B());
}

TEST(SpriteTest, CheckFlipXProperty) {
    sprite.FlipX(true);
    ASSERT_TRUE(sprite.FlipX());
}

TEST(SpriteTest, CheckFlipYProperty) {
    sprite.FlipY(true);
    ASSERT_TRUE(sprite.FlipY());
}

TEST(SpriteTest, CheckSortingLayerProperty) {
    sprite.SortingLayer(12);
    ASSERT_EQ(12, sprite.SortingLayer());
}

TEST(SpriteTest, CheckOrderInLayerroperty) {
    sprite.OrderInLayer(99);
    ASSERT_EQ(99, sprite.OrderInLayer());
}