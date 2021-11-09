#ifndef SPIC_ENGINE_ANIMATORSUBSYSTEM_HPP
#define SPIC_ENGINE_ANIMATORSUBSYSTEM_HPP

#include "ISubsystem.hpp"

namespace engine {
    class AnimatorSubsystem : public ISubsystem {
    public:
        void Update() override;
    };
}

#endif //SPIC_ENGINE_ANIMATORSUBSYSTEM_HPP
