#ifndef SPIC_ENGINE_PHYSICSSUBSYSTEM_H
#define SPIC_ENGINE_PHYSICSSUBSYSTEM_H

#include <box2d/box2d.h>
#include <memory>
#include <RigidBody.hpp>
#include <vector>
#include <GameObject.hpp>
#include "ISubsystem.hpp"
#include "../Listeners/ContactListener.hpp"

namespace engine
{
    /**
     * @brief Subsystem to handle RigidBody and Collider components.
     */
    class PhysicsSubsystem : public ISubsystem
    {
        private:
            std::hash<std::string> _hasher = {};
            std::unique_ptr<ContactListener> _contactListener = {};
            std::unique_ptr<b2World> _physicsWorld = {};

            /**
             * @brief Converts a body type to a Box2D body type.
             * @param bodyType The body type to be converted.
             * @return The body type matching the given body type.
             */
            static b2BodyType TranslateBodyType(spic::BodyType bodyType);

            /**
             * @brief Register a trigger for a given fixture and collider.
             * @param fixtureDef The fixtures the collider will be registered to.
             * @param collider The collider that will be registered.
             */
            void RegisterTrigger(b2FixtureDef& fixtureDef, const std::shared_ptr<spic::Collider>& collider);

            /**
             * @brief Constructs a new Box2D body for a given game object and their rigid body.
             * @param rigidBody The rigid body linked to the game object.
             * @param gameObject The game object.
             * @param width The width of the body.
             * @param height The height of the body.
             * @return
             */
            b2Body* MakeBody(const spic::RigidBody& rigidBody, spic::GameObject& gameObject, double width, double height);

            /**
             * @brief Adds physics to a given shape.
             * @param body The body of the shape.
             * @param shape The shape to add physics to.
             * @param rigidBody The rigid body of the shape.
             * @param collider The collider of the shape.
             * @param area The area that will be covered in physics.
             */
            void AddPhysicsToShape(b2Body* body, b2Shape* shape, const std::shared_ptr<spic::RigidBody>& rigidBody, const std::shared_ptr<spic::Collider>& collider, double area);

        public:
            /**
             * @brief Handles the physics world every frame to prevent collisions and handle triggers.
             */
            void Update() override;

            /**
             * @brief Constructs a new instance of a PhysicsSubsytem.
             */
            PhysicsSubsystem();
    };
}


#endif //SPIC_ENGINE_PHYSICSSUBSYSTEM_H
