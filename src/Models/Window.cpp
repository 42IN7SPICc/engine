#pragma clang diagnostic push
#pragma ide diagnostic ignored "cppcoreguidelines-narrowing-conversions"

#include <stdexcept>
#include <cmath>
#include <SDL.h>
#include "Window.hpp"

using namespace engine;

Window::Window(const std::string &title, int xpos, int ypos, int width, int height, bool fullscreen) : _window(nullptr, &SDL_DestroyWindow),
                                                                                                       _renderer(nullptr, &SDL_DestroyRenderer),
                                                                                                       _textureManager(new TextureManager) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) throw std::runtime_error("SDL2 could not be initialized");

    if (fullscreen) {
        SDL_DisplayMode DM;
        if (SDL_GetDesktopDisplayMode(0, &DM) != 0) throw std::runtime_error("SDL2 Desktop display mode could not be determined");
        _window.reset(SDL_CreateWindow(title.c_str(), 0, 0, DM.w, DM.h, SDL_WINDOW_BORDERLESS));
    } else {
        _window.reset(SDL_CreateWindow(title.c_str(), xpos, ypos, width, height, SDL_WINDOW_SHOWN));
    }

    if (!_window) throw std::runtime_error("SDL2 could not initialize a window");

    _renderer.reset(SDL_CreateRenderer(_window.get(), -1, 0));

    if (!_renderer) throw std::runtime_error("SDL2 could not initialize a renderer");

    if (SDL_SetRenderDrawColor(_renderer.get(), 0, 0, 0, 255) != 0)
        throw std::runtime_error(SDL_GetError());
}

void Window::Render(const std::string &texturePath, const spic::Transform &transform, const SDL_RendererFlip &flip) {
    auto texture = _textureManager->GetTexture(_renderer.get(), texturePath);
    SDL_Rect rect;
    rect.x = transform.position.x;
    rect.y = transform.position.y;
    rect.w = texture->Width() * transform.scale;
    rect.h = texture->Height() * transform.scale;

    SDL_RenderCopyEx(_renderer.get(), texture->Get(), nullptr, &rect, std::fmod(transform.rotation, 360), nullptr, flip);
}

void Window::SwapBuffers() {
    SDL_RenderPresent(_renderer.get());
}

void Window::Clear() {
    SDL_RenderClear(_renderer.get());
}

#pragma clang diagnostic pop