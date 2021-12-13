#include "RectangleUtil.hpp"

#include <cmath>

using namespace engine;
using namespace spic;

std::vector<Point> RectangleUtil::Rotate(const Point& center, double width, double height, double angle)
{
    std::vector<Point> points{};

    auto wDiff = width * 0.5;
    auto hDiff = height * 0.5;

    auto cAngle = cos(angle);
    auto wCos = wDiff * cAngle;
    auto hCos = hDiff * cAngle;

    auto sAngle = sin(angle);
    auto wSin = wDiff * sAngle;
    auto hSin = hDiff * sAngle;

    points.push_back({center.x - wCos - hSin, center.y - wSin + hCos});
    points.push_back({center.x + wCos - hSin, center.y + wSin + hCos});
    points.push_back({center.x + wCos + hSin, center.y + wSin - hCos});
    points.push_back({center.x - wCos + hSin, center.y - wSin - hCos});

    return points;
}
