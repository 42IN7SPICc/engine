#include "SDLMixerException.hpp"

#include "SDL_mixer.h"

engine::SDLMixerException::SDLMixerException(const std::string& message) : EngineException(message, Mix_GetError())
{
}
