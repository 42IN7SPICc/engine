#include "Component.hpp"

#include <utility>

using namespace spic;

Component::Component() : active{true}, _gameObject{}
{
}

std::weak_ptr<spic::GameObject> Component::GameObject() const
{
    return _gameObject;
}

void Component::GameObject(std::weak_ptr<spic::GameObject> gameObject)
{
    _gameObject = std::move(gameObject);
}