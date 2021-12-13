#ifndef SPIC_ENGINE_PHYSICSBEHAVIOUR_HPP
#define SPIC_ENGINE_PHYSICSBEHAVIOUR_HPP

#include "BehaviourScript.hpp"

class PhysicsBehaviour : public spic::BehaviourScript
{
    private:
        std::shared_ptr<spic::GameObject> _ball;

    public:
        explicit PhysicsBehaviour(std::shared_ptr<spic::GameObject>& ball);

        void OnStart() override;

        void OnUpdate() override;

        void OnTriggerEnter2D(const spic::Collider& collider) override;

        void OnTriggerExit2D(const spic::Collider& collider) override;

        void OnTriggerStay2D(const spic::Collider& collider) override;
};


#endif //SPIC_ENGINE_PHYSICSBEHAVIOUR_HPP
