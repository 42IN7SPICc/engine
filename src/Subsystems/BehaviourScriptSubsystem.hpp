#ifndef SPIC_ENGINE_BEHAVIOURSCRIPTSUBSYSTEM_HPP
#define SPIC_ENGINE_BEHAVIOURSCRIPTSUBSYSTEM_HPP

#include "ISubsystem.hpp"

namespace engine
{
    /**
     * @brief Subsystem to handle BehaviourScript components.
     */
    class BehaviourScriptSubsystem : public ISubsystem
    {
        public:
            /**
             * @brief Triggers the OnStart method for unstarted scripts and the OnUpdate method for scripts that have been started.
             */
            void Update() override;
    };
}

#endif //SPIC_ENGINE_BEHAVIOURSCRIPTSUBSYSTEM_HPP
