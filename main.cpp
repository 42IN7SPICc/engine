#include "Api.hpp"
#include "TestApplyForce.hpp"
#include "TestApplyForceReverse.hpp"
#include "CircleCollider.hpp"
#include "BoxCollider.hpp"
#include "RigidBody.hpp"

using namespace spic;

std::shared_ptr<GameObject> CreateBall(bool is_reversed = false) {
    float ballScale = 0.2;
    float ballSize = 1100;

    auto TestObject = std::make_shared<GameObject>("test", "test", 0);
    TestObject->Transform().scale = ballScale;

    if(is_reversed) {
        TestObject->Transform().position.x = 510;
        TestObject->Transform().position.y = 510;
    }

    std::shared_ptr<spic::BehaviourScript> Script {};
    if(is_reversed)
        Script = std::make_shared<TestApplyForceReverse>();
    else
        Script = std::make_shared<TestApplyForce>();

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

    return TestObject;
}

int main(int argc, char* args[])
{
    Engine& engine = Engine::Instance();
    EngineConfig engineConfig{WindowConfig{"Engine Test Window", 1366, 768, false}};
    engine.Init(engineConfig);

    auto scene = std::make_shared<Scene>();
    engine.PushScene(scene);

    auto TestObject = CreateBall();
    auto TestObjectReversed = CreateBall(true);

    scene->Contents().push_back(TestObject);
    scene->Contents().push_back(TestObjectReversed);
    engine.Start();

    return 0;
}
