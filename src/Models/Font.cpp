#include "Font.hpp"

using namespace engine;

Font::Font(TTF_Font* font) : _font{font, &TTF_CloseFont} {
}

TTF_Font* Font::GetFont() const {
    return _font.get();
}
