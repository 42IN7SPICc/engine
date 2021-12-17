#include "UpdateBehaviourScriptSubsystem.hpp"

void engine::UpdateBehaviourScriptSubsystem::Handle(const std::shared_ptr<spic::BehaviourScript>& behaviourScript)
{
    if (!behaviourScript->Started())
    {
        behaviourScript->Started(true);
        behaviourScript->OnStart();
    }
    behaviourScript->OnUpdate();
}
