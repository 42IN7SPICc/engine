#ifndef SPIC_ENGINE_FONT_HPP
#define SPIC_ENGINE_FONT_HPP

#include "SDL_ttf.h"

#include <memory>

namespace engine {
    class Font {
    private:
        std::unique_ptr<TTF_Font, decltype(&TTF_CloseFont)> _font;

    public:
        explicit Font(TTF_Font *font);

        [[nodiscard]] TTF_Font *GetFont() const;
    };
}

#endif //SPIC_ENGINE_FONT_HPP
