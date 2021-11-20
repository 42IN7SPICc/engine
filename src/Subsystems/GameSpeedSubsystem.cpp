#include "GameSpeedSubsystem.hpp"
#include <Input.hpp>
#include <Time.hpp>

#define MAX_TIME_SCALE 2.0
#define MIN_TIME_SCALE 0.5
#define TIME_SCALE_STEP 0.1

void engine::GameSpeedSubsystem::Update()
{
    if (spic::Input::GetKeyDown(spic::Input::KeyCode::PAGE_UP))
    {
        auto timeScale = spic::Time::TimeScale();
        if (timeScale < MAX_TIME_SCALE)
            spic::Time::TimeScale(timeScale + TIME_SCALE_STEP);
    }
    else if (spic::Input::GetKeyDown(spic::Input::KeyCode::PAGE_DOWN))
    {
        auto timeScale = spic::Time::TimeScale();
        if (timeScale > MIN_TIME_SCALE)
            spic::Time::TimeScale(timeScale - TIME_SCALE_STEP);
    }
    else if (spic::Input::GetKeyDown(spic::Input::KeyCode::HOME))
    {
        spic::Time::TimeScale(1.0);
    }
}
