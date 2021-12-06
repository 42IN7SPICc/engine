#ifndef SPIC_ENGINE_SDLTTFEXCEPTION_HPP
#define SPIC_ENGINE_SDLTTFEXCEPTION_HPP

#include "EngineException.hpp"

namespace engine
{
    class SDLTTFException : public EngineException
    {
        public:
            SDLTTFException(const std::string& message);

            std::string InnerMessage() override;
    };
}

#endif //SPIC_ENGINE_SDLTTFEXCEPTION_HPP
