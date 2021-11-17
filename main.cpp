#include "Api.hpp"
#include "TestApplyForce.hpp"
#include "CircleCollider.hpp"
#include "BoxCollider.hpp"
#include "RigidBody.hpp"

using namespace spic;

int main(int argc, char* args[])
{
    Engine& engine = Engine::Instance();
    EngineConfig engineConfig{WindowConfig{"Engine Test Window", 1366, 768, false}};
    engine.Init(engineConfig);

    auto scene = std::make_shared<Scene>();
    engine.PushScene(scene);

    float ballScale = 0.2;
    float ballSize = 1100;

    auto TestObject = std::make_shared<GameObject>("test", "test", 0);
    TestObject->Transform().scale = ballScale;

    auto Script = std::make_shared<TestApplyForce>();
    Script->GameObject(TestObject);
    TestObject->AddComponent(Script);

    auto Collider = std::make_shared<CircleCollider>((ballSize / 2) * ballScale);
    Collider->GameObject(TestObject);
    TestObject->AddComponent(Collider);

    auto RigidBody = std::make_shared<spic::RigidBody>(24,24, BodyType::dynamicBody);
    RigidBody->GameObject(TestObject);
    TestObject->AddComponent(RigidBody);

    auto TestObjectSprite = std::make_shared<Sprite>("resources/ball.png",false, false, 0,0);
    TestObjectSprite->GameObject(TestObject);
    TestObject->AddComponent(TestObjectSprite);

    scene->Contents().push_back(TestObject);
    engine.Start();

    return 0;
}
