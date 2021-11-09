#include "TimeManager.hpp"
#include "Debug.hpp"
#include "SDL_timer.h"

using namespace engine;

const double MAX_DELTA_TIME = 200.0;
TimeManager TimeManager::_instance{};

double TimeManager::DeltaTime() const {
    return _deltaTime * 1000;
}

double TimeManager::TimeScale() const {
    return _timeScale;
}

void TimeManager::TimeScale(double newTimeScale) {
    _timeScale = newTimeScale;
}

void TimeManager::Update() {
    _lastTick = _currentTick;
    _currentTick = SDL_GetPerformanceCounter();

    if (_lastTick == -1) {
        _lastTick = _currentTick;
    }

    auto deltaTime = (double) ((_currentTick - _lastTick) * 1000 / (double) SDL_GetPerformanceFrequency()); // NOLINT(cppcoreguidelines-narrowing-conversions)

    if (deltaTime > MAX_DELTA_TIME) {
        spic::Debug::Log("Can't keep up! Did the system time change, or is the application overloaded? Running " + std::to_string(deltaTime) + "ms behind, skipping ticks");
        deltaTime = MAX_DELTA_TIME;
    }

    _deltaTime = deltaTime;
}

TimeManager &TimeManager::GetInstance() {
    return _instance;
}