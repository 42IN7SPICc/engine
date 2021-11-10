#include "RigidBody.hpp"

using namespace spic;

RigidBody::RigidBody(double mass, double gravityScale, const BodyType &bodyType) : mass(mass), gravityScale(gravityScale), bodyType(bodyType) {}

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

void RigidBody::AddForce(const Point &forceDirection) {
    //TODO implement
}

