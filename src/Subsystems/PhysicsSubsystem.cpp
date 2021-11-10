#include "PhysicsSubsystem.hpp"

#include <memory>
#include <cmath>
#include <vector>
#include <map>

#include "GameObject.hpp"
#include "Collider.hpp"
#include "RigidBody.hpp"
#include "CircleCollider.hpp"
#include "BoxCollider.hpp"

using namespace engine;
using namespace spic;

const int32 velocityIterations = 6;
const int32 positionIterations = 2;
const float timeStep = 1.0f / 60.0f;
const double pixelScale = 1.0;

PhysicsSubsystem::PhysicsSubsystem() : _contactListener(std::make_unique<ContactListener>()) {
    b2Vec2 gravity(0.0f, 2.0f);
    _physicsWorld = std::make_unique<b2World>(gravity);
}

void PhysicsSubsystem::Update() {
    // Currently, all the gameObject and the PhysicsWorld get rebuild every Update tick.
    // The reason for this is because of the complex implementation of Box2D inside the SPIC API
    // We needed a lot of extra variables and function to get updated correctly working.
    // The only problem with the current setup is a little performance loss, and some physics inaccuracy
    b2Vec2 gravity(0.0f, 2.0f);
    _physicsWorld = std::make_unique<b2World>(gravity);
    _physicsWorld->SetContactListener(_contactListener.get());
    std::vector<std::tuple<b2Body *, std::shared_ptr<GameObject>>> newObjectLocations;
    std::map<std::shared_ptr<GameObject>, Transform> oldTransforms;

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
                fixtureDef.userData = *reinterpret_cast<b2FixtureUserData *>(circleCollider.get());

                if (circleCollider->IsTrigger()) {
                    fixtureDef.isSensor = true;
                    std::hash<std::string> hash;
                    fixtureDef.filter.categoryBits = hash(gameObject->Tag());
                }

                body->CreateFixture(&fixtureDef);
            } else {
                b2FixtureDef fixtureDef;
                fixtureDef.shape = &circleShape;
                fixtureDef.density = 0.0f;
                fixtureDef.userData = *reinterpret_cast<b2FixtureUserData *>(circleCollider.get());

                if (circleCollider->IsTrigger()) {
                    fixtureDef.isSensor = true;
                    std::hash<std::string> hash;
                    fixtureDef.filter.categoryBits = hash(gameObject->Tag());
                }

                body->CreateFixture(&fixtureDef);
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
                fixtureDef.userData = *reinterpret_cast<b2FixtureUserData *>(boxCollider.get());

                if (boxCollider->IsTrigger()) {
                    fixtureDef.isSensor = true;
                    std::hash<std::string> hash;
                    fixtureDef.filter.categoryBits = hash(gameObject->Tag());
                }

                body->CreateFixture(&fixtureDef);
            } else {
                b2FixtureDef fixtureDef;
                fixtureDef.shape = &boxShape;
                fixtureDef.density = 0.0f;
                fixtureDef.userData = *reinterpret_cast<b2FixtureUserData *>(boxCollider.get());

                if (boxCollider->IsTrigger()) {
                    fixtureDef.isSensor = true;
                    std::hash<std::string> hash;
                    fixtureDef.filter.categoryBits = hash(gameObject->Tag());
                }

                body->CreateFixture(&fixtureDef);
            }
        }

        newObjectLocations.emplace_back(std::make_tuple(body, gameObject));
        oldTransforms.insert(std::make_pair(gameObject, gameObject->AbsoluteTransform()));
    }

    //run physics simulation
    for (int32 i = 0; i < 60; ++i) {
        _physicsWorld->Step(timeStep, velocityIterations, positionIterations);
    }

    //update location of game objects
    for (const auto &newObjectLocation: newObjectLocations) {
        const auto&[body, gameObject] = newObjectLocation;
        auto transform = oldTransforms[gameObject];

        for (auto boxCollider: gameObject->GetComponents<BoxCollider>()) {
            gameObject->Transform().position.x += ((body->GetPosition().x - boxCollider->Width() / 2.0) / pixelScale) - transform.position.x;
            gameObject->Transform().position.y += ((body->GetPosition().y - boxCollider->Height() / 2.0) / pixelScale) - transform.position.y;
            gameObject->Transform().rotation = (body->GetAngle() * 180 / b2_pi);// - transform.rotation;
        }

        for (auto circleCollider: gameObject->GetComponents<CircleCollider>()) {
            gameObject->Transform().position.x += ((body->GetPosition().x - circleCollider->Radius()) / pixelScale) - transform.position.x;
            gameObject->Transform().position.y += ((body->GetPosition().y - circleCollider->Radius()) / pixelScale) - transform.position.y;
            gameObject->Transform().rotation = (body->GetAngle() * 180 / b2_pi);// - transform.rotation;
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
    auto transform = gameObject.AbsoluteTransform();
    bodyDef.position.Set((float) (transform.position.x + width / 2.0) * pixelScale,
                         (float) (transform.position.y + height / 2.0) * pixelScale);
    bodyDef.angle = (float) gameObject.Transform().rotation * b2_pi / 180;
    return _physicsWorld->CreateBody(&bodyDef);
}
