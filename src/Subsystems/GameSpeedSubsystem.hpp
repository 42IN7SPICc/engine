#ifndef SPIC_ENGINE_GAMESPEEDSUBSYSTEM_HPP
#define SPIC_ENGINE_GAMESPEEDSUBSYSTEM_HPP

#include "ISubsystem.hpp"

namespace engine
{
    /**
     * @brief Subsystem to handle game speed changes.
     */
    class GameSpeedSubsystem : public ISubsystem
    {
        public:
            /**
             * @brief Checks whether keeps have been pressed which have actions to increase, decrease or reset the game speed.
             */
            void Update() override;
    };
}

#endif //SPIC_ENGINE_GAMESPEEDSUBSYSTEM_HPP
