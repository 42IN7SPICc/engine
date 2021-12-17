#ifndef SPIC_ENGINE_LATEUPDATEBEHAVIOURSCRIPTSUBSYSTEM_HPP
#define SPIC_ENGINE_LATEUPDATEBEHAVIOURSCRIPTSUBSYSTEM_HPP

#include "BehaviourScriptSubsystem.hpp"

namespace engine
{
    class LateUpdateBehaviourScriptSubsystem : public BehaviourScriptSubsystem
    {
        protected:
            /**
             * @brief Handles the stuff to be done for a script in the current BehaviourScriptSubsystem.
             * @param behaviourScript The script to handle.
             */
            void Handle(const std::shared_ptr<spic::BehaviourScript>& behaviourScript) override;
    };
}

#endif //SPIC_ENGINE_LATEUPDATEBEHAVIOURSCRIPTSUBSYSTEM_HPP
