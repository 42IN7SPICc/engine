#ifndef SPIC_ENGINE_DEBUGLINES_HPP
#define SPIC_ENGINE_DEBUGLINES_HPP

#include <vector>
#include "Point.hpp"
#include "Color.hpp"

namespace engine
{
    /**
     * @brief A struct containing information for one line
     */
    struct DebugLine
    {
        DebugLine(const spic::Point& from, const spic::Point& to, const spic::Color& color) : from(from),
                                                                                              to(to),
                                                                                              color(color)
        {
        }

        spic::Point from;
        spic::Point to;
        spic::Color color;
    };

    /**
     * @brief A struct containing all lines to be drawn
     */
    struct DebugLines
    {
        public:
            /**
             * @brief Access to all the debug lines
             * @return The instance of the debug lines vector.
             */
            static std::vector<DebugLine>& Lines();
            static void Clear();

        private:
            static DebugLines _instance;
            std::vector<DebugLine> _lines;
    };
}

#endif //SPIC_ENGINE_DEBUGLINES_HPP
