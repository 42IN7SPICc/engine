#include "Utils/PointUtil.hpp"

#define _USE_MATH_DEFINES

#include <cmath>

using namespace spic;

Point PointUtil::CalculateDirectionalPoint(const Point& from, const Point& to, double multiplier)
{
    auto pointDiff = PointDiff(from, to);
    auto distance = Distance(pointDiff);
    return {pointDiff.x / distance * multiplier, pointDiff.y / distance * multiplier};
}

Point PointUtil::CalculateDirectionalPoint(const Point& from, const Point& to, double multiplier, double& distance)
{
    auto pointDiff = PointDiff(from, to);
    distance = Distance(pointDiff);
    return {pointDiff.x / distance * multiplier, pointDiff.y / distance * multiplier};
}

double PointUtil::Distance(const Point& from, const Point& to)
{
    auto pointDiff = PointDiff(from, to);
    return sqrt(pointDiff.x * pointDiff.x + pointDiff.y * pointDiff.y);
}

double PointUtil::Distance(const Point& pointDiff)
{
    return sqrt(pointDiff.x * pointDiff.x + pointDiff.y * pointDiff.y);
}

Point PointUtil::PointDiff(const Point& point1, const Point& point2)
{
    return {point2.x - point1.x, point2.y - point1.y};
}

double PointUtil::Degrees(const Point& point1, const Point& point2)
{
    return atan2(point1.y - point2.y, point1.x - point2.x) * 180 / M_PI - 90;
}
