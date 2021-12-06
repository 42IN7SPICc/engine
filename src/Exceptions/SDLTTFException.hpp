#ifndef SPIC_ENGINE_SDLTTFEXCEPTION_HPP
#define SPIC_ENGINE_SDLTTFEXCEPTION_HPP

#include "EngineException.hpp"

namespace engine
{
    class SDLTTFException : public EngineException
    {
        public:
            explicit SDLTTFException(const std::string& message);
    };
}

#endif //SPIC_ENGINE_SDLTTFEXCEPTION_HPP
