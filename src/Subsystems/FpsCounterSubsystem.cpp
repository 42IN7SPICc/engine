#include "FpsCounterSubsystem.hpp"
#include "../Managers/TimeManager.hpp"
#include "Input.hpp"
#include "Engine.hpp"

using namespace engine;

FpsCounterSubsystem::FpsCounterSubsystem(Window* window) : _window(window), _enabled(false)
{
#ifndef NDEBUG
    _enabled = true;
#endif
}

void FpsCounterSubsystem::Update()
{
    if (spic::Input::GetKeyDown(spic::Input::KeyCode::F3))
    {
        _enabled = !_enabled;
    }

    if (_enabled)
    {
        _window->RenderTextRaw(std::to_string(static_cast<int>(1 / TimeManager::GetInstance().DeltaTime())), spic::Engine::Instance().Config().window.width - 25, 25, "resources/fonts/arial.ttf", 18);
    }
}
