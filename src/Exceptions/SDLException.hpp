#ifndef SPIC_ENGINE_SDLEXCEPTION_HPP
#define SPIC_ENGINE_SDLEXCEPTION_HPP

#include "EngineException.hpp"

namespace engine
{
    /**
     * @brief An exception that handles errors for SDL.
     */
    class SDLException : public EngineException
    {
        public:
            /**
             * @brief Generates a new sdl exception with a given message.
             * @param message The message describing the error.
             */
            explicit SDLException(const std::string& message);
    };
}

#endif //SPIC_ENGINE_SDLEXCEPTION_HPP
