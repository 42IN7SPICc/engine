#include "RigidBody.hpp"
#include <gtest/gtest.h>

//RigidBody::RigidBody(double mass, double gravityScale, const BodyType& bodyType) : mass{mass},
//                                                                                   gravityScale{gravityScale},
//                                                                                   bodyType{bodyType},
//                                                                                   _point(std::make_unique<spic::Point>())
//{
//}
//BodyType RigidBody::Type() const;
//void RigidBody::Type(BodyType newBodyType);
//double RigidBody::Mass() const;
//void RigidBody::Mass(double newMass);
//double RigidBody::GravityScale() const;
//void RigidBody::GravityScale(double newGravityScale);
//void RigidBody::AddForce(const spic::Point& forceDirection);
//void RigidBody::Point(const spic::Point& point);


TEST(RigidBodyTest, RigidBodyType) {
    spic::RigidBody body {100, 25, spic::BodyType::dynamicBody};
    ASSERT_EQ(spic::BodyType::dynamicBody , body.Type());
}