#include "ContactListener.hpp"

#include <GameObject.hpp>
#include <BehaviourScript.hpp>

using namespace engine;

void ContactListener::BeginContact(b2Contact* contact)
{
    spic::Component* entityA;
    spic::Component* entityB;
    if (GetEntities(contact, entityA, entityB))
    {
        if (entityA->GameObject().expired() || entityB->GameObject().expired()) return;
        auto gameObjectA = entityA->GameObject().lock();
        auto gameObjectB = entityB->GameObject().lock();
        auto scripts = gameObjectA->GetComponents<spic::BehaviourScript>();
        for (const auto& script: scripts)
        {
            auto collider = gameObjectB->GetComponent<spic::Collider>();
            script->OnTriggerStay2D(*collider);

            if (!_currentCollisions.contains(script))
                _currentCollisions[script] = {};

            _currentCollisions[script].push_back(collider);

            if (!_previousCollisions.contains(script) || std::find(_previousCollisions[script].begin(), _previousCollisions[script].end(), collider) == _previousCollisions[script].end())
            {
                script->OnTriggerEnter2D(*collider);
            }
        }
    }
}

void ContactListener::EndContact(b2Contact* contact)
{
    spic::Component* entityA;
    spic::Component* entityB;
    if (GetEntities(contact, entityA, entityB))
    {
        if (entityA->GameObject().expired() || entityB->GameObject().expired()) return;
        auto gameObjectA = entityA->GameObject().lock();
        auto gameObjectB = entityB->GameObject().lock();
        auto scripts = gameObjectA->GetComponents<spic::BehaviourScript>();
        for (const auto& script: scripts)
        {
            auto collider = gameObjectB->GetComponent<spic::Collider>();
            script->OnTriggerExit2D(*collider);
        }
    }
}

bool ContactListener::GetEntities(b2Contact* contact, spic::Component*& entityA, spic::Component*& entityB)
{
    b2Fixture* fixtureA = contact->GetFixtureA();
    b2Fixture* fixtureB = contact->GetFixtureB();

    //make sure only one of the fixtures was a sensor
    bool sensorA = fixtureA->IsSensor();
    bool sensorB = fixtureB->IsSensor();
    if (!(sensorA ^ sensorB))
        return false;

    b2FixtureUserData& objectA = fixtureA->GetUserData();
    b2FixtureUserData& objectB = fixtureB->GetUserData();

    auto componentA = reinterpret_cast<spic::Component*>(objectA.pointer);
    auto componentB = reinterpret_cast<spic::Component*>(objectB.pointer);

    if (sensorA)
    {
        entityA = componentA;
        entityB = componentB;
    }
    else
    {
        entityA = componentB;
        entityB = componentA;
    }

    return true;
}

void ContactListener::StartNewPhysicsSession()
{
    _previousCollisions = std::move(_currentCollisions);
    _currentCollisions = {};
}
