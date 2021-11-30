#ifndef SPIC_ENGINE_TEXTURE_HPP
#define SPIC_ENGINE_TEXTURE_HPP

#include <string>
#include <memory>

#include <SDL_render.h>

namespace engine
{
    /**
     * @brief Stores a SDL Surface and Texture prevent memory leaks upon shutdown.
     */
    class Texture
    {
        private:
            std::unique_ptr<SDL_Surface, decltype(&SDL_FreeSurface)> _surface;
            std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)> _texture;

            int _width = 0;
            int _height = 0;

        public:
            /**
             * @brief Constructs a new Font with a given surface and texture.
             * @param surface The given SDL Surface.
             * @param texture The given SDL Texture.
             */
            Texture(SDL_Surface* surface, SDL_Texture* texture);

            /**
             * @brief Access the SDL Texture inside the model.
             * @return The texture that is stored.
             */
            [[nodiscard]] SDL_Texture* Get() const;

            /**
             * @brief Access the SDL Surface inside the model.
             * @return The surface that is stored.
             */
            [[nodiscard]] SDL_Surface* Surface() const;

            /**
             * @brief Access the width of the texture.
             * @return The width of the texture.
             */
            [[nodiscard]] const int& Width() const;

            /**
             * @brief Access the height of the texture.
             * @return The height of the texture.
             */
            [[nodiscard]] const int& Height() const;

            /**
             * @brief Disable the copy operator to prevent memory leaks.
             * @param texture The other texture.
             * @return The new texture.
             */
            Texture& operator=(const Texture& texture) = delete;

            /**
             * @brief Disable the copy constructor to prevent memory leaks.
             * @param texture The other texture.
             */
            Texture(const Texture& texture) = delete;
    };
}


#endif //SPIC_ENGINE_TEXTURE_HPP
