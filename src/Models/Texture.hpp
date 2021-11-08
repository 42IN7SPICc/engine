#ifndef SPIC_ENGINE_TEXTURE_HPP
#define SPIC_ENGINE_TEXTURE_HPP

#include <string>
#include <memory>

#include <SDL_render.h>

namespace engine {
    class Texture {
    private:
        std::unique_ptr<SDL_Surface, decltype(&SDL_FreeSurface)> _surface;
        std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)> _texture;

        int _width;
        int _height;

    public:
        Texture(SDL_Surface *surface, SDL_Texture *texture);

        [[nodiscard]] SDL_Texture *Get() const;

        [[nodiscard]] SDL_Surface *Surface() const;

        [[nodiscard]] const int &Width() const;

        [[nodiscard]] const int &Height() const;

        Texture &operator=(const Texture &texture) = delete;

        Texture(const Texture &texture) = delete;
    };
}


#endif //SPIC_ENGINE_TEXTURE_HPP
