#ifndef SPIC_ENGINE_SDLIMAGEEXCEPTION_HPP
#define SPIC_ENGINE_SDLIMAGEEXCEPTION_HPP

#include "EngineException.hpp"

namespace engine
{
    class SDLImageException : public EngineException
    {
        public:
            explicit SDLImageException(const std::string& message);
    };
}

#endif //SPIC_ENGINE_SDLIMAGEEXCEPTION_HPP
