#include "Engine.hpp"
#include "Subsystems/Subsystems.hpp"
#include "Managers/TimeManager.hpp"
#include "SDL_timer.h"

using namespace spic;

const int TARGET_FPS = 60;
const double TARGET_FRAME_DELAY = 1000.0 / TARGET_FPS;

Engine Engine::instance{};

void Engine::Init(const EngineConfig &config) {
    _config = config;
}

EngineConfig &Engine::Config() {
    return _config;
}

Engine &Engine::Instance() {
    return instance;
}

void Engine::Start() {
    std::vector<std::shared_ptr<engine::ISubsystem>> subsystems = {
            std::make_shared<engine::InputSubsystem>(),
            std::make_shared<engine::BehaviourScriptSubsystem>(),
            std::make_shared<engine::AnimatorSubsystem>(),
            std::make_shared<engine::RenderSubsystem>(),
    };
    _running = true;

    while (!_scenes.empty() && _running) {
        auto &timeManager = engine::TimeManager::GetInstance();
        timeManager.Update();

        for (auto &subsystem: subsystems) {
            subsystem->Update();
        }

        auto deltaTimeMs = timeManager.DeltaTime() * 1000;
        if (TARGET_FRAME_DELAY > deltaTimeMs) {
            SDL_Delay(TARGET_FRAME_DELAY - deltaTimeMs); // NOLINT(cppcoreguidelines-narrowing-conversions)
        }
    }

    while (!_scenes.empty()) {
        _scenes.pop();
    }
}

void Engine::PushScene(const std::shared_ptr<Scene> &scene) {
    _scenes.push(scene);
}

std::shared_ptr<Scene> Engine::PeekScene() const {
    if (_scenes.empty()) {
        return {};
    }
    return _scenes.top();
}

void Engine::PopScene() {
    _scenes.pop();
}

void Engine::Shutdown() {
    _running = false;
}
