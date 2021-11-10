#include "RigidBody.hpp"

using namespace spic;

RigidBody::RigidBody(double mass, double gravityScale, const BodyType &bodyType) : mass(mass), gravityScale(gravityScale), bodyType(bodyType) {
    _point = std::make_unique<spic::Point>();
}

BodyType RigidBody::Type() const {
    return bodyType;
}

void RigidBody::Type(BodyType newBodyType) {
    bodyType = newBodyType;
}

double RigidBody::Mass() const {
    return mass;
}

void RigidBody::Mass(double newMass) {
    mass = newMass;
}

double RigidBody::GravityScale() const {
    return gravityScale;
}

void RigidBody::GravityScale(double newGravityScale) {
    gravityScale = newGravityScale;
}

void RigidBody::AddForce(const spic::Point &forceDirection) {
    Point(forceDirection);
}

void RigidBody::Point(const spic::Point &point) {
    _point = std::make_unique<spic::Point>(point);
}

spic::Point& RigidBody::Point() const {
    return *_point;
}