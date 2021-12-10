#include "Point.hpp"

using namespace spic;

Point spic::operator+(Point lhs, const Point& rhs)
{
    lhs += rhs;
    return lhs;
}

Point spic::operator-(Point lhs, const Point& rhs)
{
    lhs -= rhs;
    return lhs;
}

Point& Point::operator+=(const Point& rhs)
{
    x += rhs.x;
    y += rhs.y;
    return *this;
}

Point& Point::operator-=(const Point& rhs)
{
    x -= rhs.x;
    y -= rhs.y;
    return *this;
}
