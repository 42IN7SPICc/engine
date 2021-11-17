#include "TestApplyForceReverse.hpp"
#include "Debug.hpp"
#include "GameObject.hpp"
#include "RigidBody.hpp"
#include "Input.hpp"
#include "BoxCollider.hpp"
#include "CircleCollider.hpp"
#include "Sprite.hpp"

const float ballScale = 0.2;
const float ballSize = 1100;

void TestApplyForceReverse::OnStart()
{
    _isBox = false;
    _parent = GameObject().lock();
    _rigidBody = _parent->GetComponent<spic::RigidBody>();
    _collider = _parent->GetComponent<spic::CircleCollider>();
    _sprite = _parent->GetComponent<spic::Sprite>();
    spic::Debug::Log("TestApplyForce Started");
}

void TestApplyForceReverse::OnUpdate()
{
    if (spic::Input::GetKeyDown(spic::Input::KeyCode::RIGHT_CONTROL))
    {
        _parent->RemoveComponent(_collider);
        if (_isBox)
        {
            auto Collider = std::make_shared<spic::CircleCollider>((ballSize / 2) * ballScale);
            Collider->GameObject(_parent);
            _parent->AddComponent(Collider);
            _collider = Collider;
            _isBox = false;
            _sprite->Texture("resources/ball.png");
        }
        else
        {
            auto Collider = std::make_shared<spic::BoxCollider>(ballSize * ballScale, ballSize * ballScale);
            Collider->GameObject(_parent);
            _parent->AddComponent(Collider);
            _collider = Collider;
            _isBox = true;
            _sprite->Texture("resources/ball_2.png");
        }
    }

    if (spic::Input::GetKey(spic::Input::KeyCode::DOWN_ARROW))
    {
        _rigidBody->AddForce({-10, -10});
    }
    if (spic::Input::GetKey(spic::Input::KeyCode::UP_ARROW))
    {
        _rigidBody->AddForce({10, 10});
    }
}

void TestApplyForceReverse::OnTriggerEnter2D(const spic::Collider& collider)
{
    BehaviourScript::OnTriggerEnter2D(collider);
}

void TestApplyForceReverse::OnTriggerExit2D(const spic::Collider& collider)
{
    BehaviourScript::OnTriggerExit2D(collider);
}

void TestApplyForceReverse::OnTriggerStay2D(const spic::Collider& collider)
{
    BehaviourScript::OnTriggerStay2D(collider);
}
