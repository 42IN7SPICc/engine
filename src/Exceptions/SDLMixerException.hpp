#ifndef SPIC_ENGINE_SDLMIXEREXCEPTION_HPP
#define SPIC_ENGINE_SDLMIXEREXCEPTION_HPP

#include "EngineException.hpp"

namespace engine
{
    class SDLMixerException : public EngineException
    {
        public:
            SDLMixerException(const std::string& message);

            std::string InnerMessage() override;
    };
}

#endif //SPIC_ENGINE_SDLMIXEREXCEPTION_HPP
