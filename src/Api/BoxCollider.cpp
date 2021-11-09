#include "BoxCollider.hpp"

using namespace spic;

BoxCollider::BoxCollider() {
    this->width = 0;
    this->height = 0;
}

BoxCollider::BoxCollider(double width, double height) : width(width), height(height) {}