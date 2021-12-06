#include "SDLException.hpp"

#include <SDL_error.h>

engine::SDLException::SDLException(const std::string& message) : EngineException(message)
{
}

std::string engine::SDLException::InnerMessage()
{
    return SDL_GetError();
}
