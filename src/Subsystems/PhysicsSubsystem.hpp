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
    class PhysicsSubsystem : public ISubsystem
    {
        private:
            std::hash<std::string> _hasher = {};
            std::unique_ptr<ContactListener> _contactListener = {};
            std::unique_ptr<b2World> _physicsWorld = {};

            static b2BodyType TranslateBodyType(spic::BodyType bodyType);
            void RegisterTrigger(b2FixtureDef& fixtureDef, const std::shared_ptr<spic::Collider>& collider);

            b2Body* MakeBody(const spic::RigidBody& rigidBody, spic::GameObject& gameObject, double width, double height);
            void AddPhysicsToShape(b2Body* body, b2Shape* shape, const std::shared_ptr<spic::RigidBody>& rigidBody, const std::shared_ptr<spic::Collider>& collider, double area);
        public:
            void Update() override;

            PhysicsSubsystem();
    };
}


#endif //SPIC_ENGINE_PHYSICSSUBSYSTEM_H
