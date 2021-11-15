#include "BoxCollider.hpp"

using namespace spic;

BoxCollider::BoxCollider() : BoxCollider(0, 0)
{
}

BoxCollider::BoxCollider(double width, double height) : width(width), height(height)
{
}