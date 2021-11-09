#include "Time.hpp"
#include "../Managers/TimeManager.hpp"

using namespace spic;

double Time::DeltaTime() {
    return TimeManager::GetInstance().DeltaTime();
}

double Time::TimeScale() {
    return TimeManager::GetInstance().TimeScale();
}

void Time::DeltaTime(double newDeltaTime) {
    TimeManager::GetInstance().DeltaTime(newDeltaTime);
}

void Time::TimeScale(double newTimeScale) {
    TimeManager::GetInstance().TimeScale(newTimeScale);
}