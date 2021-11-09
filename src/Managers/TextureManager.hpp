#ifndef SPIC_ENGINE_TEXTUREMANAGER_HPP
#define SPIC_ENGINE_TEXTUREMANAGER_HPP

#include "../Models/Texture.hpp"

#include <map>
#include <memory>
#include <string>

namespace engine {
    class TextureManager {
    private:
        std::map<std::string, std::shared_ptr<Texture>> _textures;
    public:
        void LoadTexture(SDL_Renderer *renderer, const std::string &path);

        std::shared_ptr<Texture> GetTexture(SDL_Renderer *renderer, const std::string &path);

        [[nodiscard]] bool Contains(const std::string &path) const;
    };
}


#endif //SPIC_ENGINE_TEXTUREMANAGER_HPP
