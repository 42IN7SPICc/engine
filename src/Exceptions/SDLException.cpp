#include "SDLException.hpp"

#include <SDL_error.h>

engine::SDLException::SDLException(const std::string& message) : EngineException(message, SDL_GetError())
{
}
