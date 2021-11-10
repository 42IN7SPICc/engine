#include "CircleCollider.hpp"

using namespace spic;

CircleCollider::CircleCollider() : CircleCollider(0) {
    IsTrigger(false);
}

CircleCollider::CircleCollider(double radius) : radius(radius) {
    IsTrigger(false);
}
