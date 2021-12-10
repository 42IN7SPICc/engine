#pragma clang diagnostic push
#pragma ide diagnostic ignored "cppcoreguidelines-narrowing-conversions"

#include <stdexcept>
#include <cmath>
#include <SDL.h>
#include "Window.hpp"
#include "../Exceptions/SDLException.hpp"

using namespace engine;

Window::Window(const std::string& title, int xpos, int ypos, int width, int height, bool fullscreen) : _window(nullptr, &SDL_DestroyWindow),
                                                                                                       _renderer(nullptr, &SDL_DestroyRenderer),
                                                                                                       _textureManager(new TextureManager),
                                                                                                       _fontManager(new FontManager),
                                                                                                       _backgroundColor(spic::Color::black())
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0) throw SDLException("The Video API could not be initialized.");

    if (fullscreen)
    {
        SDL_DisplayMode DM{};
        if (SDL_GetDesktopDisplayMode(0, &DM) != 0) throw SDLException("The Video API could not determine the display mode of the desktop.");
        _window.reset(SDL_CreateWindow(title.c_str(), 0, 0, DM.w, DM.h, SDL_WINDOW_FULLSCREEN));
    }
    else
    {
        _window.reset(SDL_CreateWindow(title.c_str(), xpos, ypos, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE));
    }

    if (!_window) throw SDLException("The Video API could not initialize a window.");

    _renderer.reset(SDL_CreateRenderer(_window.get(), -1, SDL_RENDERER_ACCELERATED));

    if (!_renderer) throw SDLException("The Video API could not initialize a renderer.");

    RenderColor(spic::Color::black());

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(_renderer.get(), width, height);
}

void Window::Render(const std::string& texturePath, const spic::Transform& transform, const SDL_RendererFlip& flip, const spic::Color& color)
{
    auto texture = _textureManager->GetTexture(_renderer.get(), texturePath, color);
    SDL_FRect rect{};
    rect.w = texture->Width() * transform.scale;
    rect.h = texture->Height() * transform.scale;
    rect.x = transform.position.x - rect.w / 2.0;
    rect.y = transform.position.y - rect.h / 2.0;

    SDL_RenderCopyExF(_renderer.get(), texture->Get(), nullptr, &rect, std::fmod(transform.rotation, 360), nullptr, flip);
}

void Window::RenderText(const std::string& text, const spic::Transform& transform, const std::string& fontPath, int size, spic::Alignment alignment, spic::Color color, double maxWidth)
{
    auto font = _fontManager->GetFont(fontPath, size);
    SDL_Color sdlColor{
            static_cast<Uint8>(color.R() * 255),
            static_cast<Uint8>(color.G() * 255),
            static_cast<Uint8>(color.B() * 255),
            static_cast<Uint8>(color.A() * 255)
    };
    SDL_Surface* surface = TTF_RenderUTF8_Blended_Wrapped(font->GetFont(), text.c_str(), sdlColor, maxWidth);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(_renderer.get(), surface);

    auto newTransform = transform;
    if (alignment == spic::Alignment::left || alignment == spic::Alignment::right)
    {
        double widthDiff = maxWidth - surface->w;
        if (widthDiff < 0) widthDiff = 0;

        newTransform.position.x += (alignment == spic::Alignment::left ? -(widthDiff / 2) : widthDiff / 2) * newTransform.scale;
    }

    SDL_FRect rect{};
    rect.w = surface->w * newTransform.scale;
    rect.h = surface->h * newTransform.scale;
    rect.x = newTransform.position.x - rect.w / 2.0;
    rect.y = newTransform.position.y - rect.h / 2.0;

    SDL_RenderCopyF(_renderer.get(), texture, nullptr, &rect);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}

void Window::RenderTextRaw(const std::string& text, double x, double y, const std::string& fontPath, int size)
{
    RenderText(text, spic::Transform{{x, y}, 1, 1}, fontPath, size, spic::Alignment::center, spic::Color::red(), 1000);
}

spic::Point Window::WindowSize() const
{
    int x{};
    int y{};
    SDL_GetWindowSize(_window.get(), &x, &y);
    return {static_cast<double>(x), static_cast<double>(y)};
}

void Window::SwapBuffers()
{
    SDL_RenderPresent(_renderer.get());
}

void Window::Clear()
{
    RenderColor(_backgroundColor);
    SDL_RenderClear(_renderer.get());
    RenderColor(spic::Color::black());
}

void Window::RenderScale(float* xScale, float* yScale) const
{
    SDL_RenderGetScale(_renderer.get(), xScale, yScale);
}

void Window::RenderLine(double fromX, double fromY, double toX, double toY, const spic::Color& color)
{
    RenderColor(color);
    SDL_RenderDrawLine(_renderer.get(), fromX, fromY, toX, toY);
    RenderColor(spic::Color::black());
}

void Window::RenderColor(const spic::Color& color)
{
    if (SDL_SetRenderDrawColor(_renderer.get(), color.R() * 255, color.G() * 255, color.B() * 255, color.A() * 255) != 0)
    {
        throw SDLException("The Video API could not set the draw color.");
    }
}

void Window::BackgroundColor(const spic::Color& backgroundColor)
{
    _backgroundColor = backgroundColor;
}

#pragma clang diagnostic pop
