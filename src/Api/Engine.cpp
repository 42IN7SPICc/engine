#include "Engine.hpp"
#include "../Subsystems/Subsystems.hpp"
#include "../Managers/TimeManager.hpp"
#include "SDL_timer.h"
#include <stdexcept>
#include <iostream>

using namespace spic;

const int TARGET_FPS = 60;
const double TARGET_FRAME_DELAY = 1000.0 / TARGET_FPS;

Engine Engine::instance{};

Engine::Engine() : _scenes{}, _config{}, _running{false}
{
}

void Engine::Init(const EngineConfig& config)
{
    _config = config;
}

EngineConfig& Engine::Config()
{
    return _config;
}

Engine& Engine::Instance()
{
    return instance;
}

void Engine::Start()
{
    auto& windowConfig = Config().window;
    auto window = std::make_unique<engine::Window>(windowConfig.title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowConfig.width, windowConfig.height, windowConfig.fullscreen);

    std::vector<std::shared_ptr<engine::ISubsystem>> subsystems = {
            std::make_shared<engine::AudioSubsystem>(),
            std::make_shared<engine::InputSubsystem>(),
            std::make_shared<engine::GameSpeedSubsystem>(),
            std::make_shared<engine::AnimatorSubsystem>(),
            std::make_shared<engine::UpdateBehaviourScriptSubsystem>(),
            std::make_shared<engine::PhysicsSubsystem>(),
            std::make_shared<engine::LateUpdateBehaviourScriptSubsystem>(),
            std::make_shared<engine::RenderSubsystem>(window.get()),
            std::make_shared<engine::FpsCounterSubsystem>(window.get())
    };
    _running = true;

    while (!_scenes.empty() && _running)
    {
        uint64_t start = SDL_GetPerformanceCounter();
        _currentScene = _scenes.top();
        auto& timeManager = engine::TimeManager::GetInstance();
        timeManager.Update();

        window->Clear();
        for (auto& subsystem: subsystems)
        {
            subsystem->Update();
        }
        window->SwapBuffers();
        std::flush(std::cout);

        float elapsedMs = (SDL_GetPerformanceCounter() - start) / static_cast<float>(SDL_GetPerformanceFrequency()) * 1000.0f; // NOLINT(cppcoreguidelines-narrowing-conversions)
        if (TARGET_FRAME_DELAY > elapsedMs)
        {
            SDL_Delay(TARGET_FRAME_DELAY - elapsedMs); // NOLINT(cppcoreguidelines-narrowing-conversions)
        }
    }

    while (!_scenes.empty())
    {
        _scenes.pop();
    }
}

void Engine::PushScene(const std::shared_ptr<Scene>& scene)
{
    if (_currentScene) engine::AudioSubsystem::PauseAllAudioPlayback();
    _scenes.push(scene);
}

std::shared_ptr<Scene> Engine::PeekScene() const
{
    if (!_currentScene) throw std::runtime_error("There is no available scene to load.");
    return _currentScene;
}

void Engine::PopScene()
{
    auto poppedScene = _scenes.top();
    _scenes.pop();

    std::shared_ptr<spic::Scene> destinationScene{};

    if (!_scenes.empty())
        destinationScene = _scenes.top();
    else
        destinationScene = std::make_shared<spic::Scene>();

    engine::AudioSubsystem::StopAllAudioPlayback(poppedScene, destinationScene);
}

void Engine::Shutdown()
{
    _running = false;
}