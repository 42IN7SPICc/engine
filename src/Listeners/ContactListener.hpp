#ifndef SPIC_ENGINE_CONTACTLISTENER_HPP
#define SPIC_ENGINE_CONTACTLISTENER_HPP

#include <box2d/box2d.h>
#include <Component.hpp>
#include <map>
#include <BehaviourScript.hpp>
#include <vector>

class ContactListener : public b2ContactListener
{
    public:
        void StartNewPhysicsSession();

        void BeginContact(b2Contact* contact) override;

        void EndContact(b2Contact* contact) override;

    private:
        std::map<std::shared_ptr<spic::BehaviourScript>, std::vector<std::shared_ptr<spic::Collider>>> _currentCollisions = {};
        std::map<std::shared_ptr<spic::BehaviourScript>, std::vector<std::shared_ptr<spic::Collider>>> _previousCollisions = {};

        static bool GetEntities(b2Contact* contact, spic::Component*& entityA, spic::Component*& entityB);
};


#endif //SPIC_ENGINE_CONTACTLISTENER_HPP
