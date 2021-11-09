#include <stdexcept>
#include "TextureManager.hpp"
#include "SDL_image.h"

using namespace engine;

void TextureManager::LoadTexture(SDL_Renderer *renderer, const std::string &path) {
    if (Contains(path)) return;

    auto tempSurface = IMG_Load(path.c_str());
    if (!tempSurface) {
        throw std::runtime_error("SDL2_Image: image could not be loaded.");
    }

    auto tempTexture = SDL_CreateTextureFromSurface(renderer, tempSurface);
    if (tempTexture == nullptr) {
        throw std::runtime_error("SDL2_Image: texture could not be created.");
    }
    auto texture = std::make_shared<Texture>(tempSurface, tempTexture);
    _textures.insert_or_assign(path, texture);
}

std::shared_ptr<Texture> TextureManager::GetTexture(SDL_Renderer *renderer, const std::string &path) {
    if (Contains(path)) return _textures[path];

    LoadTexture(renderer, path);
    return _textures[path];
}

bool TextureManager::Contains(const std::string &path) const {
    return _textures.count(path) > 0;
}
