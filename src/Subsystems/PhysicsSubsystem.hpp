#ifndef SPIC_ENGINE_PHYSICSSUBSYSTEM_H
#define SPIC_ENGINE_PHYSICSSUBSYSTEM_H

#include "ISubsystem.hpp"
#include <box2d/box2d.h>
#include <memory>
#include "RigidBody.hpp"
#include <vector>
#include "GameObject.hpp"
#include "../Models/ContactListener.hpp"

namespace engine {
    class PhysicsSubsystem : public ISubsystem {
    private:
        std::unique_ptr<ContactListener> _contactListener;
        std::unique_ptr<b2World> _physicsWorld;
        b2BodyType TranslateBodyType(spic::BodyType bodyType);
        b2Body* MakeBody(const spic::RigidBody &rigidBody, spic::GameObject &gameObject, double width, double height);
    public:
        void Update() override;
        PhysicsSubsystem();
    };
}


#endif //SPIC_ENGINE_PHYSICSSUBSYSTEM_H
