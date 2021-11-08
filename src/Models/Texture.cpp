#include "Texture.hpp"

#ifndef NDEBUG

#include "iostream"

#endif

using namespace engine;

void DestructTexture(SDL_Texture *tex) {
    SDL_DestroyTexture(tex);
#ifndef NDEBUG
    std::cout << "Destroying texture" << std::endl;
#endif
}

Texture::Texture(SDL_Surface *surface, SDL_Texture *texture) : _surface(surface, &SDL_FreeSurface),
                                                               _texture(texture, &DestructTexture),
                                                               _width(0),
                                                               _height(0) {
    SDL_QueryTexture(texture, nullptr, nullptr, &_width, &_height);
}

SDL_Texture *Texture::Get() const {
    return _texture.get();
}

SDL_Surface *Texture::Surface() const {
    return _surface.get();
}

const int &Texture::Width() const {
    return _width;
}

const int &Texture::Height() const {
    return _height;
}