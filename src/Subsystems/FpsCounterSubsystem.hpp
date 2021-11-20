#ifndef SPIC_ENGINE_FPSCOUNTERSUBSYSTEM_HPP
#define SPIC_ENGINE_FPSCOUNTERSUBSYSTEM_HPP

#include "ISubsystem.hpp"
#include "../Models/Window.hpp"

namespace engine {
    class FpsCounterSubsystem : public ISubsystem {
        private:
            Window* _window;
        public:
            explicit FpsCounterSubsystem(Window* window);

            void Update() override;
    };
}

#endif //SPIC_ENGINE_FPSCOUNTERSUBSYSTEM_HPP
