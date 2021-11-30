#ifndef SPIC_ENGINE_TEXTUREMANAGER_HPP
#define SPIC_ENGINE_TEXTUREMANAGER_HPP

#include "../Models/Texture.hpp"

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
        public:
            /**
             * @brief Create a new cache item for a given texture.
             * @param renderer The renderer to convert the file to a texture.
             * @param path The path to the texture file.
             */
            void LoadTexture(SDL_Renderer* renderer, const std::string& path);

            /**
             * @brief Get a Texture from the cache of textures.
             * @param renderer The renderer to access the texture from.
             * @param path The path to the texture file.
             * @return The cached texture.
             */
            std::shared_ptr<Texture> GetTexture(SDL_Renderer* renderer, const std::string& path);

            /**
             * @brief Checks whether a cache item exists for a given path.
             * @param path the path to the texture file.
             * @return Whether the cache item exists.
             */
            [[nodiscard]] bool Contains(const std::string& path) const;
    };
}


#endif //SPIC_ENGINE_TEXTUREMANAGER_HPP
