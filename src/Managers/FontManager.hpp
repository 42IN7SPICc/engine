#ifndef SPIC_ENGINE_FONTMANAGER_HPP
#define SPIC_ENGINE_FONTMANAGER_HPP

#include "../Models/Font.hpp"

#include <map>
#include <memory>
#include <string>

namespace engine {
    class FontManager {
    private:
        static FontManager _instance;

        std::map<std::string, std::shared_ptr<Font>> _fonts;

        static std::string GetKey(const std::string &path, int size);

    public:
        FontManager();

        void LoadFont(const std::string &path, int size);

        std::shared_ptr<Font> GetFont(const std::string &path, int size);

        [[nodiscard]] bool Contains(const std::string &path, int size) const;

        static FontManager &GetInstance();
    };
}

#endif //SPIC_ENGINE_FONTMANAGER_HPP
