#include "Api.hpp"

using namespace spic;

class TestBehavior : public BehaviourScript
{
    public:
        void OnStart() override
        {
            //
        }

        void OnUpdate() override
        {
            Debug::DrawLine({1,1}, {500,500}, spic::Color::lime());
        }

        void OnTriggerEnter2D(const Collider& collider) override
        {
            //
        }

        void OnTriggerExit2D(const Collider& collider) override
        {
            //
        }

        void OnTriggerStay2D(const Collider& collider) override
        {
            //
        }

};

int main(int argc, char* args[])
{
    Engine& engine = Engine::Instance();
    EngineConfig engineConfig{WindowConfig{"Engine Test Window", 1366, 768, false}};
    engine.Init(engineConfig);

    auto test = std::make_shared<GameObject>("Test", "Test", 1);
    auto testBeh = std::make_shared<TestBehavior>();
    test->AddComponent(testBeh);
    testBeh->GameObject(test);

    auto scene = std::make_shared<Scene>();
    scene->Contents().push_back(test);
    engine.PushScene(scene);
    engine.Start();

    return 0;
}