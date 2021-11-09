#include "RectangleUtil.hpp"

#include <cmath>

using namespace engine;
using namespace spic;

std::vector<Point> RectangleUtil::Rotate(const Point& center, double width, double height, double angle) {
    std::vector<Point> points{};

    points.push_back({center.x - ((width / 2) * cos(angle)) - ((height / 2) * sin(angle)), center.y - ((width / 2) * sin(angle)) + ((height / 2) * cos(angle))});
    points.push_back({center.x + ((width / 2) * cos(angle)) - ((height / 2) * sin(angle)), center.y + ((width / 2) * sin(angle)) + ((height / 2) * cos(angle))});
    points.push_back({center.x + ((width / 2) * cos(angle)) + ((height / 2) * sin(angle)), center.y + ((width / 2) * sin(angle)) - ((height / 2) * cos(angle))});
    points.push_back({center.x - ((width / 2) * cos(angle)) + ((height / 2) * sin(angle)), center.y - ((width / 2) * sin(angle)) - ((height / 2) * cos(angle))});

    return points;
}
