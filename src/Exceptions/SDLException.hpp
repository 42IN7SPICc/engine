#ifndef SPIC_ENGINE_SDLEXCEPTION_HPP
#define SPIC_ENGINE_SDLEXCEPTION_HPP

#include "EngineException.hpp"

namespace engine
{
    class SDLException : public EngineException
    {
        public:
            explicit SDLException(const std::string& message);

            std::string InnerMessage() override;
    };
}

#endif //SPIC_ENGINE_SDLEXCEPTION_HPP
