#ifndef SPIC_ENGINE_TEXTUREMANAGER_HPP
#define SPIC_ENGINE_TEXTUREMANAGER_HPP

#include "../Models/Texture.hpp"

#include "Color.hpp"

#include <map>
#include <memory>
#include <string>

namespace engine
{
    /**
     * @brief Caches multiple textures to prevent the Engine from accessing files multiple times.
     */
    class TextureManager
    {
        private:
            std::map<size_t, std::shared_ptr<Texture>> _textures = {};
            std::hash<std::string> _stringHasher = {};

            /**
             * @brief Convert a path and a color to a texture hash.
             * @warning There's a small chance that there will be hash collisions. Visually confirm all color settings before release
             * @param path The path to the texture file.
             * @param color The color to use for the overlay.
             * @return The hash of a texture with a color suffix.
             */
            [[nodiscard]] size_t ComputeTextureHash(std::string path, const spic::Color& color) const;

        public:
            /**
             * @brief Create a new cache item for a given texture.
             * @param renderer The renderer to convert the file to a texture.
             * @param path The path to the texture file.
             * @param color The color tint to overlay with the texture.
             */
            void LoadTexture(SDL_Renderer* renderer, const std::string& path, const spic::Color& color);

            /**
             * @brief Get a Texture from the cache of textures.
             * @param renderer The renderer to access the texture from.
             * @param path The path to the texture file.
             * @param color The color tint to overlay with the texture.
             * @return The cached texture.
             */
            std::shared_ptr<Texture> GetTexture(SDL_Renderer* renderer, const std::string& path, const spic::Color& color);

            /**
             * @brief Checks whether a cache item exists for a given path.
             * @param path The path to the texture file.
             * @param color The color tint to overlay with the texture.
             * @return Whether the cache item exists.
             */
            [[nodiscard]] bool Contains(const std::string& path, const spic::Color& color) const;
    };
}


#endif //SPIC_ENGINE_TEXTUREMANAGER_HPP
