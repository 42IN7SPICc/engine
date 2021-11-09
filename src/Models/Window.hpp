#ifndef SPIC_ENGINE_WINDOW_HPP
#define SPIC_ENGINE_WINDOW_HPP

#include "Transform.hpp"
#include "../Managers/TextureManager.hpp"
#include <SDL_video.h>
#include <SDL_render.h>

namespace engine {

    class Window {
    private:
        std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> _window;
        std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> _renderer;
        std::unique_ptr<TextureManager> _textureManager;

    public:
        Window(const std::string &title, int xpos, int ypos, int width, int height, bool fullscreen);

        void Render(const std::string &texturePath, const spic::Transform &transform, const SDL_RendererFlip &flip);

        void SwapBuffers();

        void Clear();
    };
}


#endif //SPIC_ENGINE_WINDOW_HPP
