#ifndef SPIC_ENGINE_INPUTSUBSYSTEM_HPP
#define SPIC_ENGINE_INPUTSUBSYSTEM_HPP

#include "ISubsystem.hpp"

namespace engine {
    class InputSubsystem : public ISubsystem {
    public:
        void Update() override;
    };
}

#endif //SPIC_ENGINE_INPUTSUBSYSTEM_HPP
