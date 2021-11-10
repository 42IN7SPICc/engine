#ifndef SPIC_ENGINE_WINDOW_HPP
#define SPIC_ENGINE_WINDOW_HPP

#include "Color.hpp"
#include "Text.hpp"
#include "Transform.hpp"

#include "../Managers/FontManager.hpp"
#include "../Managers/TextureManager.hpp"

#include "SDL_render.h"
#include "SDL_video.h"

namespace engine {

    class Window {
    private:
        std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> _window;
        std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> _renderer;
        std::unique_ptr<TextureManager> _textureManager;
        std::unique_ptr<FontManager> _fontManager;

    public:
        Window(const std::string& title, int xpos, int ypos, int width, int height, bool fullscreen);

        void Render(const std::string& texturePath, const spic::Transform& transform, const SDL_RendererFlip& flip);

        void RenderText(const std::string& text, const spic::Transform& transform, const std::string& fontPath, int size, spic::Alignment alignment, spic::Color color, double maxWidth);

        void SwapBuffers();

        void Clear();
    };
}


#endif //SPIC_ENGINE_WINDOW_HPP
