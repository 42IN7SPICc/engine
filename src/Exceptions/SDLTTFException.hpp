#ifndef SPIC_ENGINE_SDLTTFEXCEPTION_HPP
#define SPIC_ENGINE_SDLTTFEXCEPTION_HPP

#include "EngineException.hpp"

namespace engine
{
    /**
     * @brief An exception that handles errors for SDL TTF.
     */
    class SDLTTFException : public EngineException
    {
        public:
            /**
             * @brief Generates a new font exception with a given message.
             * @param message The message describing the error.
             */
            explicit SDLTTFException(const std::string& message);
    };
}

#endif //SPIC_ENGINE_SDLTTFEXCEPTION_HPP
