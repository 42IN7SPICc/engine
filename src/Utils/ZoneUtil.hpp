#ifndef SPIC_ENGINE_ZONEUTIL_HPP
#define SPIC_ENGINE_ZONEUTIL_HPP

#include "Point.hpp"

#include <vector>

namespace engine
{
    /**
     * @brief A util for calculating whether a point is inside a given zone.
     */
    class ZoneUtil
    {
        public:
            /**
             * @brief Checks whether a given point is inside a given zone.
             * @param point The point to check for.
             * @param points The list of points to check within.
             * @return Whether the point is inside the zone.
             */
            static bool InZone(const spic::Point& point, const std::vector<spic::Point>& points);

            /**
             * @brief Calculate the center of a list of points.
             * @param points The list of points.
             * @return The center point.
             */
            static spic::Point GetCenter(const std::vector<spic::Point>& points);

            /**
             * @brief Get the max length a point can be from any of the corners.
             * @param points The list of corners.
             * @param center The center of the zone.
             * @return The max distance from any point to the center.
             */
            static double GetMaxLength(const std::vector<spic::Point>& points, const spic::Point& center);

        private:
            /**
             * @brief Check whether a given point is inside a given zones.
             * @param point The point to check for.
             * @param points The points that make up to zone.
             * @return Whether the point is inside the zone.
             */
            static int WindPnPoly(const spic::Point& point, const std::vector<spic::Point>& points);

            /**
             * @brief Calculate the distance between two points.
             * @param point1 The first point.
             * @param point2 The second point.
             * @return The distance between the two points.
             */
            static double GetDistance(const spic::Point& point1, const spic::Point& point2);

            /**
             * @brief Check whether a point is left of two points.
             * @param point1 The first point.
             * @param point2 The second point.
             * @param point The point to check for.
             * @return Whether the point is left of the two points.
             */
            static double IsLeft(const spic::Point& point1, const spic::Point& point2, const spic::Point& point);
    };
}

#endif //SPIC_ENGINE_ZONEUTIL_HPP
