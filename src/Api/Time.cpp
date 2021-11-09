#include "Time.hpp"

using namespace spic;

double Time::DeltaTime() {
    return TimeManager::GetInstance().DeltaTime();
}

double Time::TimeScale() {
    return TimeManager::GetInstance().TimeScale();
}

void Time::TimeScale(double newTimeScale) {
    TimeManager::GetInstance().TimeScale(newTimeScale);
}