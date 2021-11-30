#ifndef SPIC_ENGINE_FONT_HPP
#define SPIC_ENGINE_FONT_HPP

#include "SDL_ttf.h"

#include <memory>

namespace engine
{
    /**
     * @brief Stores a TTF Font to prevent memory leaks upon shutdown.
     */
    class Font
    {
        private:
            std::unique_ptr<TTF_Font, decltype(&TTF_CloseFont)> _font;

        public:
            /**
             * @brief Constructs a new Font with a given font.
             * @param font The given TTF Font
             */
            explicit Font(TTF_Font* font);

            /**
             * @brief Access the TTF Font inside the model.
             * @return The font that is stored.
             */
            [[nodiscard]] TTF_Font* GetFont() const;
    };
}

#endif //SPIC_ENGINE_FONT_HPP
