#include "ContactListener.hpp"

#include <GameObject.hpp>
#include <BehaviourScript.hpp>

void ContactListener::BeginContact(b2Contact *contact) {
    spic::Component *entityA{};
    spic::Component *entityB{};
    if (GetEntities(contact, entityA, entityB)) {
        if (entityA->GameObject().expired() || entityB->GameObject().expired()) return;
        auto gameObjectA = entityA->GameObject().lock();
        auto gameObjectB = entityB->GameObject().lock();
        auto scripts = gameObjectA->GetComponents<spic::BehaviourScript>();
        for (const auto &script: scripts) {
            auto collider = gameObjectB->GetComponent<spic::Collider>();
            script->OnTriggerStay2D(*collider);
        }
    }
}

void ContactListener::EndContact(b2Contact *contact) {
    spic::Component *entityA{};
    spic::Component *entityB{};
    if (GetEntities(contact, entityA, entityB)) {
        if (entityA->GameObject().expired() || entityB->GameObject().expired()) return;
        auto gameObjectA = entityA->GameObject().lock();
        auto gameObjectB = entityB->GameObject().lock();
        auto scripts = gameObjectA->GetComponents<spic::BehaviourScript>();
        for (const auto &script: scripts) {
            auto collider = gameObjectB->GetComponent<spic::Collider>();
            script->OnTriggerExit2D(*collider);
        }
    }
}

bool ContactListener::GetEntities(b2Contact *contact, spic::Component *&entityA, spic::Component *&entityB) {
    b2Fixture *fixtureA = contact->GetFixtureA();
    b2Fixture *fixtureB = contact->GetFixtureB();

    //make sure only one of the fixtures was a sensor
    bool sensorA = fixtureA->IsSensor();
    bool sensorB = fixtureB->IsSensor();
    if (!(sensorA ^ sensorB))
        return false;

//    b2Body *bodyA = fixtureA->GetBody();
//    b2Body *bodyB = fixtureB->GetBody();

    b2FixtureUserData &objectA = fixtureA->GetUserData();
    b2FixtureUserData &objectB = fixtureB->GetUserData();

    auto &componentA = reinterpret_cast<spic::Component &>(objectA);
    auto &componentB = reinterpret_cast<spic::Component &>(objectB);

    if (sensorA) { //fixtureB must be an enemy aircraft
        entityA = &componentA;
        entityB = &componentB;
    } else { //fixtureA must be an enemy aircraft
        entityA = &componentB;
        entityB = &componentA;
    }
    return true;
}
