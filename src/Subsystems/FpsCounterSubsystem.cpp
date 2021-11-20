#include <Time.hpp>
#include "FpsCounterSubsystem.hpp"
#include "../Managers/TimeManager.hpp"

using namespace engine;

FpsCounterSubsystem::FpsCounterSubsystem(Window* window) : _window(window)
{

}

void FpsCounterSubsystem::Update()
{
    std::string fps{std::to_string(1 / TimeManager::GetInstance().RawDeltaTime())};
    auto size = _window->WindowSize();
    _window->RenderTextRaw("Test1234", 50, 50, "resources/fonts/arial.ttf", 28);
}
