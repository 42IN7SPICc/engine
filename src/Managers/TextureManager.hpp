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
            std::map<std::string, std::shared_ptr<Texture>> _textures = {};

            /**
             * @brief Convert a path and a color to a texture path.
             * @param path The path to the texture file.
             * @param color The color to use for the overlay.
             * @return The path to a texture with a color suffix.
             */
            static std::string ComputeTexturePath(const std::string& path, const spic::Color& color);

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
