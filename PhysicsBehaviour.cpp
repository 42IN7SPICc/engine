#include "PhysicsBehaviour.hpp"
#include "Input.hpp"
#include "GameObject.hpp"
#include "RigidBody.hpp"
#include "Debug.hpp"

void PhysicsBehaviour::OnStart()
{
    //
}

void PhysicsBehaviour::OnUpdate()
{
    if(spic::Input::GetKeyDown(spic::Input::KeyCode::UP_ARROW)) {
        auto rigidBody = _ball->GetComponent<spic::RigidBody>();
        rigidBody->AddForce({0,-50});
    }
    if(spic::Input::GetKeyDown(spic::Input::KeyCode::RIGHT_ARROW)) {
        auto rigidBody = _ball->GetComponent<spic::RigidBody>();
        rigidBody->AddForce({5,0});
    }
    if(spic::Input::GetKeyDown(spic::Input::KeyCode::LEFT_ARROW)) {
        auto rigidBody = _ball->GetComponent<spic::RigidBody>();
        rigidBody->AddForce({-5,0});
    }
}

void PhysicsBehaviour::OnTriggerEnter2D(const spic::Collider& collider)
{
    spic::Debug::Log("On trigger enter: " + collider.GameObject().lock()->Name());
}

void PhysicsBehaviour::OnTriggerExit2D(const spic::Collider& collider)
{
    spic::Debug::Log("On trigger exit: " + collider.GameObject().lock()->Name());
}

void PhysicsBehaviour::OnTriggerStay2D(const spic::Collider& collider)
{
    //
}

PhysicsBehaviour::PhysicsBehaviour(std::shared_ptr<spic::GameObject>& ball) : _ball(ball)
{

}
