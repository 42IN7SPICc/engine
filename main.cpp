#include "Engine.hpp"

using namespace spic;

int main(int argc, char* args[]) {
    Engine& engine = Engine::Instance();

    EngineConfig engineConfig{WindowConfig{"Engine Test Window", 1366, 768, false}};

    engine.Init(engineConfig);

    auto scene = std::make_shared<Scene>();
    engine.PushScene(scene);

    engine.Start();

    return 0;
}
