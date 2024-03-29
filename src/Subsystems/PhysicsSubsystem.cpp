#include "PhysicsSubsystem.hpp"

#include <memory>
#include <cmath>
#include <vector>
#include <map>
#include <GameObject.hpp>
#include <RigidBody.hpp>
#include <CircleCollider.hpp>
#include <BoxCollider.hpp>
#include <Time.hpp>

using namespace engine;
using namespace spic;

const float TimeStep = 1.0f / 60.0f;
const int32 VelocityIterations = 12;
const int32 PositionIterations = 4;
const int TimeIterations = 60;
const double PixelScale = 0.5;
const double GravityScale = 10.0;

PhysicsSubsystem::PhysicsSubsystem() : _contactListener(std::make_unique<ContactListener>()), _physicsWorld(nullptr)
{
}

void PhysicsSubsystem::Update()
{
    // Currently, all the gameObject and the PhysicsWorld get rebuild every Update tick.
    // The reason for this is because of the complex implementation of Box2D inside the SPIC API
    // Alongside with the undesirable behavior of keeping the state in its current form.
    // For more information refer to the documentation
    // The only problem with the current setup is a little performance loss.
    const b2Vec2 gravity(0.0f, 0.0f);
    _physicsWorld = std::make_unique<b2World>(gravity);

    _contactListener->StartNewPhysicsSession();
    _physicsWorld->SetContactListener(_contactListener.get());

    std::vector<std::tuple<b2Body*, std::shared_ptr<GameObject>>> newObjectLocations{};
    std::map<std::shared_ptr<GameObject>, Transform> oldTransforms{};
    auto timeMultiplier = spic::Time::DeltaTime() * spic::Time::TimeScale();

    for (const auto& gameObject: GameObject::All())
    {
        auto rigidBody = gameObject->GetComponent<RigidBody>();
        if (!rigidBody) continue;

        if (rigidBody->GravityScale() != 0)
        {
            auto& rigidBodyForce = rigidBody->Point();
            rigidBodyForce.y += timeMultiplier * GravityScale * rigidBody->GravityScale();
            rigidBody->AddForce(rigidBodyForce);
        }

        b2Body* body = nullptr;

        for (const auto& circleCollider: gameObject->GetComponents<CircleCollider>())
        {
            body = MakeBody(*rigidBody, *gameObject, circleCollider->Radius() * 2, circleCollider->Radius() * 2);
            b2CircleShape circleShape{};
            circleShape.m_radius = static_cast<float>(circleCollider->Radius() * PixelScale);

            double area = rigidBody->Type() != BodyType::staticBody ? ((circleCollider->Radius() * circleCollider->Radius()) * 2) : 0.0f;
            AddPhysicsToShape(body, &circleShape, rigidBody, circleCollider, area);
        }

        for (const auto& boxCollider: gameObject->GetComponents<BoxCollider>())
        {
            body = MakeBody(*rigidBody, *gameObject, boxCollider->Width(), boxCollider->Height());
            b2PolygonShape boxShape{};
            boxShape.SetAsBox(static_cast<float>(boxCollider->Width() / 2.0 * PixelScale), static_cast<float>(boxCollider->Height() / 2.0 * PixelScale));

            double area = rigidBody->Type() != BodyType::staticBody ? (boxCollider->Width() * boxCollider->Height()) : 0.0f;
            AddPhysicsToShape(body, &boxShape, rigidBody, boxCollider, area);
        }

        auto location = rigidBody->Point();
        body->ApplyLinearImpulse(b2Vec2((float) location.x, (float) location.y), body->GetWorldCenter(), true);

        newObjectLocations.emplace_back(std::make_tuple(body, gameObject));
        oldTransforms.insert(std::make_pair(gameObject, gameObject->AbsoluteTransform()));
    }

    //run physics simulation
    for (short i = 0; i < TimeIterations; ++i)
    {
        _physicsWorld->Step(TimeStep, VelocityIterations, PositionIterations);
    }

    //update location of game objects
    for (const auto& newObjectLocation: newObjectLocations)
    {
        const auto&[body, gameObject] = newObjectLocation;
        auto transform = oldTransforms[gameObject];

        for (const auto& boxCollider: gameObject->GetComponents<BoxCollider>())
        {
            gameObject->Transform().position.x += (body->GetPosition().x / PixelScale) - transform.position.x;
            gameObject->Transform().position.y += (body->GetPosition().y / PixelScale) - transform.position.y;
            gameObject->Transform().rotation = (body->GetAngle() * 180 / b2_pi);
        }

        for (const auto& circleCollider: gameObject->GetComponents<CircleCollider>())
        {
            gameObject->Transform().position.x += (body->GetPosition().x / PixelScale) - transform.position.x;
            gameObject->Transform().position.y += (body->GetPosition().y / PixelScale) - transform.position.y;
            gameObject->Transform().rotation = (body->GetAngle() * 180 / b2_pi);
        }

        auto rigidBody = gameObject->GetComponent<RigidBody>();
        rigidBody->Point(Point());
    }
}

b2BodyType PhysicsSubsystem::TranslateBodyType(spic::BodyType bodyType)
{
    switch (bodyType)
    {
        case BodyType::dynamicBody :
            return b2BodyType::b2_dynamicBody;
        case BodyType::staticBody:
            return b2BodyType::b2_staticBody;
        case BodyType::kinematicBody:
            return b2BodyType::b2_kinematicBody;
        default:
            return b2BodyType::b2_staticBody;
    }
}

b2Body* PhysicsSubsystem::MakeBody(const RigidBody& rigidBody, GameObject& gameObject, double width, double height)
{
    b2BodyDef bodyDef{};
    bodyDef.type = TranslateBodyType(rigidBody.Type());
    auto transform = gameObject.AbsoluteTransform();
    bodyDef.position.Set(static_cast<float>((transform.position.x) * PixelScale), static_cast<float>((transform.position.y) * PixelScale));
    bodyDef.angle = (float) gameObject.Transform().rotation * b2_pi / 180;
    return _physicsWorld->CreateBody(&bodyDef);
}

void PhysicsSubsystem::RegisterTrigger(b2FixtureDef& fixtureDef, const std::shared_ptr<spic::Collider>& collider)
{
    if (collider->IsTrigger())
    {
        fixtureDef.isSensor = true;
        fixtureDef.filter.categoryBits = _hasher(collider->GameObject().lock()->Tag());
    }
}

void PhysicsSubsystem::AddPhysicsToShape(b2Body* body, b2Shape* shape, const std::shared_ptr<spic::RigidBody>& rigidBody, const std::shared_ptr<spic::Collider>& collider, double area)
{
    b2FixtureDef fixtureDef{};
    fixtureDef.shape = shape;
    if (rigidBody->Type() != BodyType::staticBody)
    {
        fixtureDef.density = (float) rigidBody->Mass() / (float) area;
    }
    else
    {
        fixtureDef.density = 0.0f;
    }
    fixtureDef.userData.pointer = reinterpret_cast<uintptr_t>(collider.get());
    RegisterTrigger(fixtureDef, collider);
    body->CreateFixture(&fixtureDef);
}
