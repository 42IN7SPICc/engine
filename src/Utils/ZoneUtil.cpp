#include "ZoneUtil.hpp"

#include <cmath>

using namespace engine;
using namespace spic;

bool ZoneUtil::InZone(const Point& point, const std::vector<Point>& points) {
    if (points.empty()) return false;

    auto center = GetCenter(points);
    if (GetDistance(point, center) < GetMaxLength(points, center))
    {
        return WindPnPoly(point, points) != 0;
    }
    return false;
}

Point ZoneUtil::GetCenter(const std::vector<Point>& points) {
    Point avgPoint{0, 0};
    if (points.empty()) return avgPoint;

    for (const auto& point: points)
    {
        avgPoint.x += point.x;
        avgPoint.y += point.y;
    }

    int pointsCount = points.size();
    avgPoint.x /= pointsCount;
    avgPoint.y /= pointsCount;

    return avgPoint;
}

double ZoneUtil::GetMaxLength(const std::vector<Point>& points, const Point& center) {
    double maxLength = 0;
    if (points.empty()) return maxLength;

    for (const auto& point: points)
    {
        auto length = GetDistance(center, point);
        if (length > maxLength) maxLength = length;
    }

    return maxLength;
}

int ZoneUtil::WindPnPoly(const Point& point, const std::vector<Point>& points) {
    auto result = 0;
    int pointsCount = points.size();
    for (int i = 0; i < pointsCount; ++i)
    {
        auto cPoint = points[i];
        auto nPoint = points[i + 1 >= pointsCount ? 0 : i + 1];

        if (cPoint.y <= point.y)
        {
            if (nPoint.y > point.y && IsLeft(cPoint, nPoint, point) > 0) result++;
        }
        else
        {
            if (nPoint.y <= point.y && IsLeft(cPoint, nPoint, point) < 0) result--;
        }
    }

    return result;
}

double ZoneUtil::GetDistance(const Point& point1, const Point& point2) {
    return sqrt(pow(point2.x - point1.x, 2) + pow(point2.y - point1.y, 2));
}

double ZoneUtil::IsLeft(const Point& point1, const Point& point2, const Point& point) {
    return (point1.x - point.x) * (point2.y - point.y) - (point2.x - point.x) * (point1.y - point.y);
}
