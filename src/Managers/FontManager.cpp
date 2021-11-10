#include "FontManager.hpp"

#include "SDL_ttf.h"

#include <stdexcept>

using namespace engine;

FontManager::FontManager() {
    if (TTF_Init() != 0) {
        throw std::runtime_error("SDL_ttf: Font could not be initialised");
    }
}

void FontManager::LoadFont(const std::string& path, int size) {
    TTF_Font* font = TTF_OpenFont(path.c_str(), size);
    if (font == nullptr) {
        throw std::runtime_error("SDL_ttf: Font file could not be loaded");
    }

    auto ttfFont = std::make_shared<Font>(font);
    _fonts[GetKey(path, size)] = ttfFont;
}

std::shared_ptr<Font> FontManager::GetFont(const std::string& path, int size) {
    auto key = GetKey(path, size);
    if (Contains(path, size)) return _fonts[key];

    LoadFont(path, size);
    return _fonts[key];
}

bool FontManager::Contains(const std::string& path, int size) const {
    return _fonts.count(GetKey(path, size)) > 0;
}

std::string FontManager::GetKey(const std::string& path, int size) {
    return {path + "_" + std::to_string(size)};
}
