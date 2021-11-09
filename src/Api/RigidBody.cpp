#include "RigidBody.hpp"

using namespace spic;

RigidBody::RigidBody(double mass, double gravityScale, const BodyType &bodyType) : mass(mass), gravityScale(gravityScale), bodyType(bodyType) {}

BodyType RigidBody::Type() const {
    return bodyType;
}

double RigidBody::Mass() const {
    return mass;
}