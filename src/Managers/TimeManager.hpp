#ifndef SPIC_ENGINE_TIMEMANAGER_HPP
#define SPIC_ENGINE_TIMEMANAGER_HPP

#include "../Models/Window.hpp"

namespace engine {

    class TimeManager {
    public:
        TimeManager() = default;

        [[nodiscard]] double DeltaTime() const;

        [[nodiscard]] double RawDeltaTime() const;

        [[nodiscard]] double TimeScale() const;

        void TimeScale(double newTimeScale);

        void Update();

        static TimeManager &GetInstance();

    private:
        static TimeManager _instance;
        uint64_t _currentTick = -1;
        uint64_t _lastTick = -1;
        double _deltaTime = 0.0;
        double _rawDeltaTime = 0.0;
        double _timeScale = 1.0;
    };
}


#endif //SPIC_ENGINE_TIMEMANAGER_HPP
