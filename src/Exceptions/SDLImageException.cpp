#include "SDLImageException.hpp"

#include "SDL_image.h"

engine::SDLImageException::SDLImageException(const std::string& message) : EngineException(message)
{
}

std::string engine::SDLImageException::InnerMessage()
{
    return IMG_GetError();
}
