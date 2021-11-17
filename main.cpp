#include "Api.hpp"

using namespace spic;

class TestScript : public spic::BehaviourScript
{
    public:
        void OnStart() override
        {
        }

        void OnUpdate() override
        {
            auto rotation = 25.0;
            auto tickRotation = rotation * Time::DeltaTime() * Time::TimeScale();

            if (Input::GetKey(spic::Input::KeyCode::E))
            {
                GameObject().lock()->Transform().rotation += tickRotation;
            }
            if (Input::GetKey(spic::Input::KeyCode::Q))
            {
                GameObject().lock()->Transform().rotation -= tickRotation;
            }
        }

        void OnTriggerEnter2D(const Collider& collider) override
        {
            BehaviourScript::OnTriggerEnter2D(collider);
        }

        void OnTriggerExit2D(const Collider& collider) override
        {
            BehaviourScript::OnTriggerExit2D(collider);
        }

        void OnTriggerStay2D(const Collider& collider) override
        {
            BehaviourScript::OnTriggerStay2D(collider);
        }
};

int main(int argc, char* args[])
{
    Engine& engine = Engine::Instance();
    EngineConfig engineConfig{WindowConfig{"Engine Test Window", 1366, 768, false}};
    engine.Init(engineConfig);

    auto scene = std::make_shared<Scene>();

    auto parentObj = std::make_shared<spic::GameObject>("parent", "parent", 5);
    parentObj->Transform().position.x = 200;
    parentObj->Transform().position.y = 200;
    auto parentScript = std::make_shared<TestScript>();
    parentScript->GameObject(parentObj);
    parentObj->AddComponent(parentScript);
    auto parentSprite = std::make_shared<spic::Sprite>("resources/hero.png", false, false, 1, 1);
    parentSprite->GameObject(parentObj);
    parentObj->AddComponent(parentSprite);

    auto childObj = std::make_shared<spic::GameObject>("child", "child", 5);
    childObj->Transform().position.x = 200;
    childObj->Parent(parentObj);
    parentObj->AddChild(childObj);
    auto childSprite = std::make_shared<spic::Sprite>("resources/hero.png", false, false, 1, 1);
    childSprite->GameObject(childObj);
    childObj->AddComponent(childSprite);

    scene->Contents().push_back(parentObj);

    engine.PushScene(scene);
    engine.Start();

    return 0;
}
