#ifndef SPIC_ENGINE_RECTANGLEUTIL_HPP
#define SPIC_ENGINE_RECTANGLEUTIL_HPP

#include "Point.hpp"

#include <vector>

namespace engine
{
    /**
     * @brief A util for manipulating rectangles.
     */
    class RectangleUtil
    {
        public:
            /**
             * @brief Rotates a rectangle with a given angle.
             * @param center The center of the rectangle.
             * @param width The width of the rectangle.
             * @param height The height of the rectangle.
             * @param angle The angle the rectangle needs to be rotated.
             * @return A list of points containing the new corners of the rectangle.
             */
            static std::vector<spic::Point> Rotate(const spic::Point& center, double width, double height, double angle);
    };
}

#endif //SPIC_ENGINE_RECTANGLEUTIL_HPP
