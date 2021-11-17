#include "BehaviourScriptSubsystem.hpp"

#include "BehaviourScript.hpp"
#include "Debug.hpp"
#include "GameObject.hpp"

using namespace engine;
using namespace spic;

void BehaviourScriptSubsystem::Update()
{
    for (const std::shared_ptr<GameObject>& gameObject: GameObject::All())
    {
        for (const std::shared_ptr<BehaviourScript>& behaviourScript: gameObject->GetComponents<BehaviourScript>())
        {
            if (behaviourScript->Active())
            {
                if (!behaviourScript->GameObject().expired())
                {
                    if (!behaviourScript->Started())
                    {
                        behaviourScript->Started(true);
                        behaviourScript->OnStart();
                    }
                    behaviourScript->OnUpdate();
                }
                else
                {
                    Debug::LogWarning("BehaviourScript does not contains a GameObject.");
                }
            }
        }
    }
}