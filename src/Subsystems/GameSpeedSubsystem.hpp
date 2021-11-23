#ifndef SPIC_ENGINE_GAMESPEEDSUBSYSTEM_HPP
#define SPIC_ENGINE_GAMESPEEDSUBSYSTEM_HPP

#include "ISubsystem.hpp"

namespace engine
{
    class GameSpeedSubsystem : public ISubsystem
    {
        public:
            void Update() override;
    };
}

#endif //SPIC_ENGINE_GAMESPEEDSUBSYSTEM_HPP
