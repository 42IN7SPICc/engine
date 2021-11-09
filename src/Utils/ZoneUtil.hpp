#ifndef SPIC_ENGINE_ZONEUTIL_HPP
#define SPIC_ENGINE_ZONEUTIL_HPP

#include "Point.hpp"

#include <vector>

namespace engine {
    class ZoneUtil {
    public:
        static bool InZone(const spic::Point& point, const std::vector<spic::Point>& points);

        static spic::Point GetCenter(const std::vector<spic::Point>& points);

        static double GetMaxLength(const std::vector<spic::Point>& points, const spic::Point& center);

    private:
        static int WindPnPoly(const spic::Point& point, const std::vector<spic::Point>& points);

        static double GetDistance(const spic::Point& point1, const spic::Point& point2);

        static double IsLeft(const spic::Point& point1, const spic::Point& point2, const spic::Point& point);
    };
}

#endif //SPIC_ENGINE_ZONEUTIL_HPP
