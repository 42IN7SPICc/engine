#ifndef SPIC_ENGINE_SDLIMAGEEXCEPTION_HPP
#define SPIC_ENGINE_SDLIMAGEEXCEPTION_HPP

#include "EngineException.hpp"

namespace engine
{
    /**
     * @brief An exception that handles errors for SDL Image.
     */
    class SDLImageException : public EngineException
    {
        public:
            /**
             * @brief Generates a new image exception with a given message.
             * @param message The message describing the error.
             */
            explicit SDLImageException(const std::string& message);
    };
}

#endif //SPIC_ENGINE_SDLIMAGEEXCEPTION_HPP
