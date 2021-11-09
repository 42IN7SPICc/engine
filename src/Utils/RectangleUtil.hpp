#ifndef SPIC_ENGINE_RECTANGLEUTIL_HPP
#define SPIC_ENGINE_RECTANGLEUTIL_HPP

#include "Point.hpp"

#include <vector>

namespace engine {
    class RectangleUtil {
    public:
        static std::vector<spic::Point> Rotate(const spic::Point& center, double width, double height, double angle);
    };
}

#endif //SPIC_ENGINE_RECTANGLEUTIL_HPP
