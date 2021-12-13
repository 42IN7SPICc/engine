#include "Utils/GameObjectUtil.hpp"

using namespace spic;

void GameObjectUtil::LinkComponent(const std::shared_ptr<spic::GameObject>& gameObject, const std::shared_ptr<spic::Component>& component)
{
    gameObject->AddComponent(component);
    component->GameObject(gameObject);
}

void GameObjectUtil::LinkChild(const std::shared_ptr<spic::GameObject>& parent, const std::shared_ptr<spic::GameObject>& child)
{
    parent->AddChild(child);
    child->Parent(parent);
}
