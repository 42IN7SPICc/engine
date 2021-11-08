#ifndef SPIC_ENGINE_RENDERSUBSYSTEM_HPP
#define SPIC_ENGINE_RENDERSUBSYSTEM_HPP

#include "ISubsystem.hpp"
#include "../Models/Window.hpp"

namespace engine {
    class RenderSubsystem : public ISubsystem {
    private:
        std::unique_ptr<Window> _window;
    public:
        RenderSubsystem();

        void Update() override;
    };
}


#endif //SPIC_ENGINE_RENDERSUBSYSTEM_HPP
