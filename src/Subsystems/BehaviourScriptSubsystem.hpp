#ifndef SPIC_ENGINE_BEHAVIOURSCRIPTSUBSYSTEM_HPP
#define SPIC_ENGINE_BEHAVIOURSCRIPTSUBSYSTEM_HPP

#include "ISubsystem.hpp"

#include "BehaviourScript.hpp"

#include <memory>

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

        protected:
            /**
             * @brief Handles the stuff to be done for a script in the current BehaviourScriptSubsystem.
             * @param behaviourScript The script to handle.
             */
            virtual void Handle(const std::shared_ptr<spic::BehaviourScript>& behaviourScript) = 0;
    };
}

#endif //SPIC_ENGINE_BEHAVIOURSCRIPTSUBSYSTEM_HPP
