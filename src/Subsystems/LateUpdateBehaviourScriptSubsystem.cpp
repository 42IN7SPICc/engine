#include "LateUpdateBehaviourScriptSubsystem.hpp"

void engine::LateUpdateBehaviourScriptSubsystem::Handle(const std::shared_ptr<spic::BehaviourScript>& behaviourScript)
{
    if (behaviourScript->Started())
    {
        behaviourScript->OnLateUpdate();
    }
}
