#include "FpsCounterSubsystem.hpp"
#include "../Managers/TimeManager.hpp"
#include "Input.hpp"

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
        auto size = _window->WindowSize();
        _window->RenderTextRaw(std::to_string(static_cast<int>(1 / TimeManager::GetInstance().DeltaTime())), size.x - 25, 2, "resources/fonts/arial.ttf", 18);
    }
}
