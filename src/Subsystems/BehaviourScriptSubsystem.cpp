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
                    Handle(behaviourScript);
                }
                else
                {
                    Debug::LogWarning("BehaviourScript does not contains a GameObject.");
                }
            }
        }
    }
}