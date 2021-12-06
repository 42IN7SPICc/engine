#include "FontManager.hpp"

#include "SDL_ttf.h"

#include "../Exceptions/SDLTTFException.hpp"

using namespace engine;

FontManager::FontManager()
{
    if (TTF_Init() != 0)
    {
        throw SDLTTFException("The Font API could not be initialized.");
    }
}

void FontManager::LoadFont(const std::string& path, int size)
{
    TTF_Font* font = TTF_OpenFont(path.c_str(), size);
    if (font == nullptr)
    {
        throw SDLTTFException("The Font API Could not load the font (" + path + ").");
    }

    auto ttfFont = std::make_shared<Font>(font);
    _fonts[GetKey(path, size)] = ttfFont;
}

std::shared_ptr<Font> FontManager::GetFont(const std::string& path, int size)
{
    auto key = GetKey(path, size);
    if (Contains(path, size)) return _fonts[key];

    LoadFont(path, size);
    return _fonts[key];
}

bool FontManager::Contains(const std::string& path, int size) const
{
    return _fonts.count(GetKey(path, size)) > 0;
}

std::string FontManager::GetKey(const std::string& path, int size)
{
    return {path + "_" + std::to_string(size)};
}
