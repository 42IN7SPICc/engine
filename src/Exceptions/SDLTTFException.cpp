#include "SDLTTFException.hpp"

#include "SDL_ttf.h"

engine::SDLTTFException::SDLTTFException(const std::string& message) : EngineException(message, TTF_GetError())
{
}
