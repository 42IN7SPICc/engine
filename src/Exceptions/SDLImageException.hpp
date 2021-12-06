#ifndef SPIC_ENGINE_SDLIMAGEEXCEPTION_HPP
#define SPIC_ENGINE_SDLIMAGEEXCEPTION_HPP

#include "EngineException.hpp"

namespace engine
{
    class SDLImageException : public EngineException
    {
        public:
            explicit SDLImageException(const std::string& message);

            std::string InnerMessage() override;
    };
}

#endif //SPIC_ENGINE_SDLIMAGEEXCEPTION_HPP
