#include "RigidBody.hpp"
#include <gtest/gtest.h>

spic::RigidBody rigidBody {0,0, spic::BodyType::dynamicBody};

TEST(RigidBodyTest, TestBodyProperty) {
    rigidBody.Type(spic::BodyType::staticBody);
    ASSERT_EQ(spic::BodyType::staticBody, rigidBody.Type());
}

TEST(RigidBodyTest, TestMassProperty) {
    rigidBody.Mass(25.5);
    ASSERT_EQ(25.5, rigidBody.Mass());
}

TEST(RigidBodyTest, TestGravityScaleProperty) {
    rigidBody.GravityScale(33.9);
    ASSERT_EQ(33.9, rigidBody.GravityScale());
}

TEST(RigidBodyTest, TestPointProperty) {
    rigidBody.Point({99.9, 1.12});
    ASSERT_EQ(99.9, rigidBody.Point().x);
    ASSERT_EQ(1.12, rigidBody.Point().y);
}

TEST(RigidBodyTest, TestAddForceMethodPositive) {
    rigidBody.Point({0.0, 0.0});
    rigidBody.AddForce({5.5, 2.5});
    ASSERT_EQ(5.5, rigidBody.Point().x);
    ASSERT_EQ(2.5, rigidBody.Point().y);
    rigidBody.AddForce({5.5, 2.5});
    ASSERT_EQ(11.0, rigidBody.Point().x);
    ASSERT_EQ(5.0,rigidBody.Point().y);
}

TEST(RigidBodyTest, TestAddForceMethodNegative) {
    rigidBody.Point({10.0, 11.0});
    rigidBody.AddForce({-5.5, -2.5});
    ASSERT_EQ(4.5, rigidBody.Point().x);
    ASSERT_EQ(8.5, rigidBody.Point().y);
    rigidBody.AddForce({-3.5, -9});
    ASSERT_EQ(1.0, rigidBody.Point().x);
    ASSERT_EQ(-0.5,rigidBody.Point().y);
}
