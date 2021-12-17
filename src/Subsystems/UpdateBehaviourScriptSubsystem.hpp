#ifndef SPIC_ENGINE_UPDATEBEHAVIOURSCRIPTSUBSYSTEM_HPP
#define SPIC_ENGINE_UPDATEBEHAVIOURSCRIPTSUBSYSTEM_HPP

#include "BehaviourScriptSubsystem.hpp"

namespace engine
{
    /**
     * @brief Handles updates for the behaviour script components.
     */
    class UpdateBehaviourScriptSubsystem : public BehaviourScriptSubsystem
    {
        protected:
            /**
             * @brief Handles the stuff to be done for a script in the current BehaviourScriptSubsystem.
             * @param behaviourScript The script to handle.
             */
            void Handle(const std::shared_ptr<spic::BehaviourScript>& behaviourScript) override;
    };
}

#endif //SPIC_ENGINE_UPDATEBEHAVIOURSCRIPTSUBSYSTEM_HPP
