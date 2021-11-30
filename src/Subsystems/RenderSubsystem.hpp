#ifndef SPIC_ENGINE_RENDERSUBSYSTEM_HPP
#define SPIC_ENGINE_RENDERSUBSYSTEM_HPP

#include "ISubsystem.hpp"
#include "../Models/Window.hpp"

namespace engine
{
    /**
     * @brief Subsystem to handle Sprite components and Text objects.
     */
    class RenderSubsystem : public ISubsystem
    {
        private:
            Window* _window;
        public:
            /**
             * @brief Constructs a new instance of a RenderSubsystem with a given window.
             * @param window The window that will be used for rendering.
             */
            explicit RenderSubsystem(Window* window);

            /**
             * @brief Accesses all the active sprites and text objects and renders them on the window.
             */
            void Update() override;
    };
}


#endif //SPIC_ENGINE_RENDERSUBSYSTEM_HPP
