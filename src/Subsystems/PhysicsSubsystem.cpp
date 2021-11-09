#include "PhysicsSubsystem.hpp"

#include <memory>
#include "GameObject.hpp"
#include "Collider.hpp"
#include "RigidBody.hpp"
#include "CircleCollider.hpp"
#include "BoxCollider.hpp"
#include <cmath>
#include <vector>

using namespace engine;
using namespace spic;

const int32 velocityIterations = 6;
const int32 positionIterations = 2;
const float timeStep = 1.0f / 60.0f;
const double pixelScale = 1.0;

PhysicsSubsystem::PhysicsSubsystem() {
    b2Vec2 gravity(0.0f, -0.1f);
    _physicsWorld = std::make_unique<b2World>(gravity);
}

void PhysicsSubsystem::Update() {
    //Define Box2D object for all GameObjects
    //TODO don't recreate the physics world, physics don't get calculated based on the previous positions
    b2Vec2 gravity(0.0f, 0.8f);
    _physicsWorld = std::make_unique<b2World>(gravity);
    std::vector<std::tuple<b2Body *, std::shared_ptr<GameObject>>> newObjectLocations;

    for (std::shared_ptr<GameObject> gameObject: GameObject::All()) {

        auto rigidBody = gameObject->GetComponent<RigidBody>();
        b2Body *body = nullptr;
        for (auto circleCollider: gameObject->GetComponents<CircleCollider>()) { //Circle
            body = MakeBody(*rigidBody, *gameObject, circleCollider->Radius() * 2, circleCollider->Radius() * 2);
            b2CircleShape circleShape;
            circleShape.m_radius = (float) circleCollider->Radius();

            if (rigidBody->Type() != BodyType::staticBody) {
                b2FixtureDef fixtureDef;
                fixtureDef.shape = &circleShape;
                double area = b2_pi * std::sqrt(circleCollider->Radius());
                fixtureDef.density = (float) rigidBody->Mass() / (float) area;
                body->CreateFixture(&fixtureDef);
            } else {
                body->CreateFixture(&circleShape, 0.0f);
            }
        }
        for (auto boxCollider: gameObject->GetComponents<BoxCollider>()) { //Box
            body = MakeBody(*rigidBody, *gameObject, boxCollider->Width(), boxCollider->Height());
            b2PolygonShape boxShape;
            boxShape.SetAsBox((float) boxCollider->Width() / 2, (float) boxCollider->Height() / 2);

            if (rigidBody->Type() != BodyType::staticBody) {
                b2FixtureDef fixtureDef;
                fixtureDef.shape = &boxShape;
                double area = boxCollider->Width() * boxCollider->Height();
                fixtureDef.density = (float) rigidBody->Mass() / (float) area;
                body->CreateFixture(&fixtureDef);
            } else {
                body->CreateFixture(&boxShape, .0f);
            }
        }

        newObjectLocations.emplace_back(std::make_tuple(body, gameObject));
    }

    //run physics simulation
    for(int32 i = 0; i < 60; ++i) {
        _physicsWorld->Step(timeStep, velocityIterations, positionIterations);
    }

    //update location of game objects
    for (const auto &newObjectLocation: newObjectLocations) {
        const auto&[body, gameObject] = newObjectLocation;
        //TODO Set position based on parent + pixelScale

        for (auto boxCollider: gameObject->GetComponents<BoxCollider>()) {
            gameObject->Transform().position.x = (body->GetPosition().x - boxCollider->Width() / 2.0) / pixelScale;
            gameObject->Transform().position.y = (body->GetPosition().y - boxCollider->Height() / 2.0) / pixelScale;
            gameObject->Transform().rotation = body->GetAngle() * 180 / b2_pi;
        }

        for (auto circleCollider: gameObject->GetComponents<CircleCollider>()) {
            gameObject->Transform().position.x = (body->GetPosition().x - circleCollider->Radius()) / pixelScale;
            gameObject->Transform().position.y = (body->GetPosition().y - circleCollider->Radius()) / pixelScale;
            gameObject->Transform().rotation = body->GetAngle() * 180 / b2_pi;
        }
    }
}

b2BodyType PhysicsSubsystem::TranslateBodyType(spic::BodyType bodyType) {
    switch (bodyType) {
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

b2Body *PhysicsSubsystem::MakeBody(const RigidBody &rigidBody, GameObject &gameObject, double width, double height) {
    b2BodyDef bodyDef;
    bodyDef.type = TranslateBodyType(rigidBody.Type());
    auto position = GetAbsolutePosition(gameObject);
    //setting the position of the box2d body
    bodyDef.position.Set((float) (position.x + width / 2.0) * pixelScale,
                         (float) (position.y + height / 2.0) * pixelScale);
    bodyDef.angle = (float)gameObject.Transform().rotation * b2_pi / 180;
    return _physicsWorld->CreateBody(&bodyDef);
}

spic::Point PhysicsSubsystem::GetAbsolutePosition(GameObject &gameObject) {
    GameObject object = gameObject;
    spic::Point point{gameObject.Transform().position.x, gameObject.Transform().position.y};

    while (!object.Parent().expired()) {
        object = *object.Parent().lock();
        point.x += object.Transform().position.x;
        point.y += object.Transform().position.y;
    }

    return point;
}
