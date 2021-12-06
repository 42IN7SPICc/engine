#include "Time.hpp"
#include "../Managers/TimeManager.hpp"

using namespace engine;
using namespace spic;

double Time::DeltaTime()
{
    return TimeManager::GetInstance().DeltaTime();
}

double Time::TimeScale()
{
    return TimeManager::GetInstance().TimeScale();
}

void Time::DeltaTime(double newDeltaTime)
{
    // This will not be used by the engine, because the TimeManager handles the delta time of the game.
}

void Time::TimeScale(double newTimeScale)
{
    TimeManager::GetInstance().TimeScale(newTimeScale);
}