#ifndef SPIC_ENGINE_FPSCOUNTERSUBSYSTEM_HPP
#define SPIC_ENGINE_FPSCOUNTERSUBSYSTEM_HPP

#include "ISubsystem.hpp"
#include "../Models/Window.hpp"

namespace engine
{
    /**
     * @brief Subsystem to handle show the FPS counter in the top right corner.
     */
    class FpsCounterSubsystem : public ISubsystem
    {
        private:
            Window* _window;
            bool _enabled;
        public:
            /**
             * @brief Constructs a new instance of a FpsCounterSubsystem for a given window.
             * @param window The SDL Window to show the FPS counter on.
             */
            explicit FpsCounterSubsystem(Window* window);

            /**
             * @brief Updates the FPS counter text with the new data for the current frame.
             */
            void Update() override;
    };
}

#endif //SPIC_ENGINE_FPSCOUNTERSUBSYSTEM_HPP
