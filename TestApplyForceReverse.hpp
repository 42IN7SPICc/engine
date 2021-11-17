#ifndef SPIC_ENGINE_TESTAPPYFORECEREVERSE_HPP
#define SPIC_ENGINE_TESTAPPYFORECEREVERSE_HPP

#include "BehaviourScript.hpp"
#include "Collider.hpp"
#include "RigidBody.hpp"
#include "Sprite.hpp"


class TestApplyForceReverse : public spic::BehaviourScript
{
    private:
        bool _isBox;
        std::shared_ptr<spic::GameObject> _parent;
        std::shared_ptr<spic::RigidBody> _rigidBody;
        std::shared_ptr<spic::Collider> _collider;
        std::shared_ptr<spic::Sprite> _sprite;
    public:
        void OnStart() override;

        void OnUpdate() override;

        void OnTriggerEnter2D(const spic::Collider& collider) override;

        void OnTriggerExit2D(const spic::Collider& collider) override;

        void OnTriggerStay2D(const spic::Collider& collider) override;
};


#endif