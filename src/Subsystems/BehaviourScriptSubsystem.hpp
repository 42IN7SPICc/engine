#ifndef SPIC_ENGINE_BEHAVIOURSCRIPTSUBSYSTEM_HPP
#define SPIC_ENGINE_BEHAVIOURSCRIPTSUBSYSTEM_HPP

#include "ISubsystem.hpp"

namespace engine {
    class BehaviourScriptSubsystem : public ISubsystem {
    public:
        void Update() override;
    };
}

#endif //SPIC_ENGINE_BEHAVIOURSCRIPTSUBSYSTEM_HPP
