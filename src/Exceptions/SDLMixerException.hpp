#ifndef SPIC_ENGINE_SDLMIXEREXCEPTION_HPP
#define SPIC_ENGINE_SDLMIXEREXCEPTION_HPP

#include "EngineException.hpp"

namespace engine
{
    /**
     * @brief An exception that handles errors for SDL Mixer.
     */
    class SDLMixerException : public EngineException
    {
        public:
            /**
             * @brief Generates a new audio exception with a given message.
             * @param message The message describing the error.
             */
            explicit SDLMixerException(const std::string& message);
    };
}

#endif //SPIC_ENGINE_SDLMIXEREXCEPTION_HPP
