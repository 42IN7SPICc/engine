#include "SDL2RuntimeError.hpp"

#include <SDL_error.h>

engine::SDL2RuntimeError::SDL2RuntimeError(const std::string& message) : _message(message)
{
    auto sdlError = std::string(SDL_GetError());
    if (!sdlError.empty())
    {
        _message += " (" + sdlError + ")";
    }
}

const char* engine::SDL2RuntimeError::what() const
{
    return _message.c_str();
}
