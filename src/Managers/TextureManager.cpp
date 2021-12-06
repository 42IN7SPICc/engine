#include "TextureManager.hpp"

#include "SDL_image.h"

#include "../Exceptions/SDLImageException.hpp"

#include <sstream>
#include <stdexcept>

using namespace engine;

void TextureManager::LoadTexture(SDL_Renderer* renderer, const std::string& path, const spic::Color& color)
{
    auto tempSurface = IMG_Load(path.c_str());
    if (!tempSurface)
    {
        throw SDLImageException("The Texture API could not load the texture (" + path + ").");
    }

    auto tempTexture = SDL_CreateTextureFromSurface(renderer, tempSurface);
    if (tempTexture == nullptr)
    {
        throw SDLImageException("The Texture API could not create a texture (" + path + ").");
    }

    if (color != spic::Color::transparent())
    {
        SDL_SetTextureColorMod(tempTexture, static_cast<Uint8>(color.R() * 255), static_cast<Uint8>(color.G() * 255), static_cast<Uint8>(color.B() * 255));
        SDL_SetTextureAlphaMod(tempTexture, static_cast<Uint8>(color.A() * 255));
    }

    auto texture = std::make_shared<Texture>(tempSurface, tempTexture);
    _textures.insert_or_assign(ComputeTextureHash(path, color), texture);
}

std::shared_ptr<Texture> TextureManager::GetTexture(SDL_Renderer* renderer, const std::string& path, const spic::Color& color)
{
    auto texturePath = ComputeTextureHash(path, color);
    if (Contains(path, color)) return _textures[texturePath];

    LoadTexture(renderer, path, color);
    return _textures[texturePath];
}

bool TextureManager::Contains(const std::string& path, const spic::Color& color) const
{
    return _textures.count(ComputeTextureHash(path, color)) > 0;
}

size_t TextureManager::ComputeTextureHash(std::string path, const spic::Color& color) const
{
    path += static_cast<char>(color.R() * 255);
    path += static_cast<char>(color.G() * 255);
    path += static_cast<char>(color.B() * 255);
    path += static_cast<char>(color.A() * 255);
    return _stringHasher(path);
}
