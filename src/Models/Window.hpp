#ifndef SPIC_ENGINE_WINDOW_HPP
#define SPIC_ENGINE_WINDOW_HPP

#include "Color.hpp"
#include "Text.hpp"
#include "Transform.hpp"

#include "../Managers/FontManager.hpp"
#include "../Managers/TextureManager.hpp"

#include "SDL_render.h"
#include "SDL_video.h"

namespace engine
{
    /**
     * @brief The Window that will be shown to the end user.
     */
    class Window
    {
        private:
            std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> _window;
            std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> _renderer;
            std::unique_ptr<TextureManager> _textureManager;
            std::unique_ptr<FontManager> _fontManager;

        public:
            /**
             * @brief Constructs a new Windows with given configuration settings.
             * @param title The title of the Window.
             * @param xpos The space the window will be offset from the left of the monitor.
             * @param ypos The space the window will be offset from the top of the monitor.
             * @param width The width of the window.
             * @param height The height of the window.
             * @param fullscreen Whether the window will be in windowed or fullscreen mode (true = fullscreen).
             */
            Window(const std::string& title, int xpos, int ypos, int width, int height, bool fullscreen);

            /**
             * @brief Render a texture on the window at a given location.
             * @param texturePath The path to the texture.
             * @param transform The location where the texture needs to be placed.
             * @param flip In which directions the textures needs to be flipped (horizontal, vertical, both).
             * @param color The color to render over the texture (transparent to disable).
             */
            void Render(const std::string& texturePath, const spic::Transform& transform, const SDL_RendererFlip& flip, const spic::Color& color = spic::Color::transparent());

            /**
             * @brief Render a string of text on the window at a given location.
             * @param text The content of the text.
             * @param transform The location where the texture needs to be placed.
             * @param fontPath The path to the font that will be used.
             * @param size The size of the font.
             * @param alignment The alignment of the font (left, center, right)/
             * @param color The color of the text.
             * @param maxWidth The max width of the text. Excess text will be wrapped in multiple lines.
             */
            void RenderText(const std::string& text, const spic::Transform& transform, const std::string& fontPath, int size, spic::Alignment alignment, spic::Color color, double maxWidth);

            /**
             * @brief Render a string of the on the window at a given location.
             * @param text The content of the text.
             * @param x The X position of the text.
             * @param y The Y position of the text.
             * @param fontPath The path to the font that will be used.
             * @param size The size of the font.
             */
            void RenderTextRaw(const std::string& text, double x, double y, const std::string& fontPath, int size);

            /**
             * @brief Access the size of the Window.
             * @return The size of the window in pixels stored in a point.
             */
            [[nodiscard]] spic::Point WindowSize() const;

            /**
             * @brief Swap buffers after rendering all the textures and text for a frame.
             */
            void SwapBuffers();

            /**
             * @brief Clear the window before rendering all the textures and text.
             */
            void Clear();

            /**
             * @brief Has 2 out parameters that return the y and x scale
             * @param xScale out parameter for x scale
             * @param yScale out parameter for y scale
             */
            void RenderScale(float* xScale, float* yScale) const;
    };
}


#endif //SPIC_ENGINE_WINDOW_HPP
