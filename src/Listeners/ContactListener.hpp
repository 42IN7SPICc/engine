#ifndef SPIC_ENGINE_CONTACTLISTENER_HPP
#define SPIC_ENGINE_CONTACTLISTENER_HPP

#include <box2d/box2d.h>
#include <Component.hpp>
#include <map>
#include <BehaviourScript.hpp>
#include <vector>

namespace engine
{
    /**
     * @brief Contact listeners to share data within Box2D listeners.
     */
    class ContactListener : public b2ContactListener
    {
        public:
            /**
             * @brief Starts a new physics session for the PhysicsSubsystem.
             */
            void StartNewPhysicsSession();

            /**
             * @brief Opens a new contact for the Box2D object.
             * @param contact the contact to be passed.
             */
            void BeginContact(b2Contact* contact) override;

            /**
             * @brief Closes a contact for the Box2D object.
             * @param contact the contact to be extracted.
             */
            void EndContact(b2Contact* contact) override;

        private:
            std::map<std::shared_ptr<spic::BehaviourScript>, std::vector<std::shared_ptr<spic::Collider>>> _currentCollisions = {};
            std::map<std::shared_ptr<spic::BehaviourScript>, std::vector<std::shared_ptr<spic::Collider>>> _previousCollisions = {};

            static bool GetEntities(b2Contact* contact, spic::Component*& entityA, spic::Component*& entityB);
    };
}

#endif //SPIC_ENGINE_CONTACTLISTENER_HPP
