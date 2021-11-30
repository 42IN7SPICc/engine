#ifndef SPIC_ENGINE_FONTMANAGER_HPP
#define SPIC_ENGINE_FONTMANAGER_HPP

#include "../Models/Font.hpp"

#include <map>
#include <memory>
#include <string>

namespace engine
{
    /**
     * @brief Caches multiple fonts to prevent the Engine from accessing files multiple times.
     */
    class FontManager
    {
        private:
            std::map<std::string, std::shared_ptr<Font>> _fonts = {};

            static std::string GetKey(const std::string& path, int size);

        public:
            /**
             * @brief Contructs a new FontManager.
             */
            FontManager();

            /**
             * @brief Create a new cache item for a given font.
             * @param path The path to the font file (ttf, otf, etc).
             * @param size The size of the font (px).
             */
            void LoadFont(const std::string& path, int size);

            /**
             * @brief Get a Font from the cache of fonts.
             * @param path The path to the font file (ttf, otf, etc).
             * @param size The size of the font (px).
             * @return The cached font.
             */
            std::shared_ptr<Font> GetFont(const std::string& path, int size);

            /**
             * @brief Checks whether a cache item exists for a given font and size.
             * @param path The path to the font file (ttf, otf, etc).
             * @param size The size of the font (px).
             * @return Whether the cache item exists.
             */
            [[nodiscard]] bool Contains(const std::string& path, int size) const;
    };
}

#endif //SPIC_ENGINE_FONTMANAGER_HPP
