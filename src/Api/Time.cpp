#include "Time.hpp"
#include "../Managers/TimeManager.hpp"

using namespace engine;
using namespace spic;

double Time::DeltaTime() {
    return TimeManager::GetInstance().DeltaTime();
}

double Time::TimeScale() {
    return TimeManager::GetInstance().TimeScale();
}

void Time::DeltaTime(double newDeltaTime) {
    // stub for now
    // this may not be done from the game
}

void Time::TimeScale(double newTimeScale) {
    TimeManager::GetInstance().TimeScale(newTimeScale);
}