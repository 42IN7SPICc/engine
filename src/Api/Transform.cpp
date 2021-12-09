#include "Transform.hpp"

using namespace spic;

Transform spic::operator+(Transform lhs, const Transform& rhs)
{
    lhs += rhs;
    return lhs;
}

Transform spic::operator-(Transform lhs, const Transform& rhs)
{
    lhs -= rhs;
    return lhs;
}

Transform& Transform::operator+=(const Transform& rhs)
{
    position += rhs.position;
    rotation += rhs.rotation;
    scale += rhs.scale;
    return *this;
}

Transform& Transform::operator-=(const Transform& rhs)
{
    position -= rhs.position;
    rotation -= rhs.rotation;
    scale -= rhs.scale;
    return *this;
}

Transform spic::operator+(Transform lhs, const Point& rhs)
{
    lhs.position += rhs;
    return lhs;
}
