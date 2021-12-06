#ifndef SPIC_ENGINE_SDLMIXEREXCEPTION_HPP
#define SPIC_ENGINE_SDLMIXEREXCEPTION_HPP

#include "EngineException.hpp"

namespace engine
{
    class SDLMixerException : public EngineException
    {
        public:
            explicit SDLMixerException(const std::string& message);
    };
}

#endif //SPIC_ENGINE_SDLMIXEREXCEPTION_HPP
