#include "GameObject.hpp"
#include "Engine.hpp"

#include <cmath>
#include <utility>

using namespace spic;

void spic_GameObject_ListObjects(const std::shared_ptr<GameObject> gameObject, std::vector<std::shared_ptr<GameObject>>& gameObjects, bool includeInactive = false)
{
    if (includeInactive || gameObject->Active())
    {
        gameObjects.push_back(gameObject);

        for (const auto& childObject: gameObject->Children())
        {
            spic_GameObject_ListObjects(childObject, gameObjects, includeInactive);
        }
    }
}

std::vector<std::shared_ptr<GameObject>> GameObject::All(bool includeInactive)
{
    std::vector<std::shared_ptr<GameObject>> gameObjects{};
    auto scene = Engine::Instance().PeekScene();

    for (const auto& gameObject: scene->Contents())
    {
        spic_GameObject_ListObjects(gameObject, gameObjects, includeInactive);
    }

    return gameObjects;
}

std::vector<std::shared_ptr<GameObject>> GameObject::FindGameObjectsWithTag(const std::string& tag)
{
    std::vector<std::shared_ptr<GameObject>> list{};

    for (auto obj: All())
    {
        if (obj->tag == tag && obj->Active())
        {
            list.push_back(obj);
        }
    }

    return list;
}

std::shared_ptr<GameObject> GameObject::FindWithTag(const std::string& tag)
{
    for (auto obj: All())
    {
        if (obj->tag == tag && obj->Active())
        {
            return obj;
        }
    }

    return nullptr;
}

void GameObject::Destroy(std::shared_ptr<GameObject> obj)
{
    auto scene = Engine::Instance().PeekScene();

    for (auto object: All())
    {
        if (object->name == obj->name)
        {
            scene->Contents().erase(std::remove(scene->Contents().begin(), scene->Contents().end(), obj), scene->Contents().end());
        }
    }
}

void GameObject::Destroy(Component* obj)
{
    std::shared_ptr<Component> component(obj);

    if (!component->GameObject().expired())
    {
        component->GameObject().lock()->RemoveComponent(component);
    }
}

GameObject::GameObject(const std::string& name, const std::string& tag, int layer) : active{true},
                                                                                     name{name},
                                                                                     tag{tag},
                                                                                     layer{layer},
                                                                                     _parent{},
                                                                                     _children{},
                                                                                     _components{},
                                                                                     _transform{{0, 0}, 0, 1}
{
}

GameObject::operator bool() const
{
    return IsActiveInWorld();
}

bool GameObject::operator!=(const GameObject& other) const
{
    return name != other.name;
}

bool GameObject::operator==(const GameObject& other) const
{
    return name == other.name;
}

bool GameObject::Active() const
{
    return active;
}

void GameObject::Active(bool flag)
{
    active = flag;
}

bool GameObject::IsActiveInWorld() const
{
    if (!_parent.expired())
    {
        return this->Active() && _parent.lock()->IsActiveInWorld();
    }
    return this->Active();
}

const spic::Transform& GameObject::Transform() const
{
    return _transform;
}

spic::Transform& GameObject::Transform()
{
    return _transform;
}

std::weak_ptr<GameObject> GameObject::Parent() const
{
    return _parent;
}

void GameObject::Parent(std::weak_ptr<GameObject> parent)
{
    _parent = std::move(parent);
}

const std::vector<std::shared_ptr<GameObject>>& GameObject::Children() const
{
    return _children;
}

void GameObject::AddChild(std::shared_ptr<GameObject> child)
{
    if (std::find(_children.begin(), _children.end(), child) == _children.end())
    {
        _children.push_back(child);
    }
}

void GameObject::RemoveChild(std::shared_ptr<GameObject> child)
{
    if (std::find(_children.begin(), _children.end(), child) == _children.end())
    {
        _children.erase(std::remove(_children.begin(), _children.end(), child), _children.end());
        child->_parent.reset();
    }
}

const std::string& GameObject::Name() const
{
    return name;
}

const std::string& GameObject::Tag() const
{
    return tag;
}

int GameObject::Layer() const
{
    return layer;
}

spic::Transform GameObject::AbsoluteTransform() const
{
    const GameObject* object = this;
    spic::Transform transform{object->Transform()};

    while (!object->Parent().expired())
    {
        object = object->Parent().lock().get();
        transform.position.x += object->Transform().position.x;
        transform.position.y += object->Transform().position.y;
//        transform.rotation += object->Transform().rotation;
        transform.scale *= object->Transform().scale;
    }

    transform.rotation = std::fmod(transform.rotation, 360);

    return transform;
}

void GameObject::RemoveComponent(std::shared_ptr<Component> component)
{
    _components.erase(std::remove(_components.begin(), _components.end(), component), _components.end());
}
