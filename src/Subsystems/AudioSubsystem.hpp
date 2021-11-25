#ifndef SPIC_ENGINE_AUDIOSUBSYSTEM_HPP
#define SPIC_ENGINE_AUDIOSUBSYSTEM_HPP

#include "ISubsystem.hpp"

namespace engine
{
    class AudioSubsystem : public ISubsystem
    {
        public:
            static void StopAllAudioPlayback();

            void Update() override;
    };
}

#endif //SPIC_ENGINE_AUDIOSUBSYSTEM_HPP
