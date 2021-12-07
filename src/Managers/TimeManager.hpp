#ifndef SPIC_ENGINE_TIMEMANAGER_HPP
#define SPIC_ENGINE_TIMEMANAGER_HPP

#include "../Models/Window.hpp"

namespace engine
{
    /**
     * @brief Stores the current DeltaTime and TimeScale.
     */
    class TimeManager
    {
        public:
            /**
             * @brief Constructs a new instance of a TimeManager.
             */
            TimeManager() = default;

            /**
             * @brief Access the DeltaTime for the current frame.
             * @return The delta time of the frame.
             */
            [[nodiscard]] double DeltaTime() const;

            /**
             * @brief Access the TimeScale of the Engine.
             * @return The current time scale.
             */
            [[nodiscard]] double TimeScale() const;

            /**
             * @brief Set the DeltaTime for the next frame.
             * @param newTimeScale the new delta time.
             */
            void TimeScale(double newTimeScale);

            /**
             * @brief Calculate the delta time and set it for the next frame.
             */
            void Update();

            /**
             * @brief Get the instance of the TimeManager.
             * @return
             */
            static TimeManager& GetInstance();

            /**
            * @brief Deleted copy assignment operator
            */
            TimeManager& operator=(const TimeManager& manager) = delete;

            /**
            * @brief Deleted move assignment operator
            */
            TimeManager& operator=(TimeManager&& manager) = delete;

            /**
            * @brief Deleted copy constructor
            */
            TimeManager(const TimeManager& manager) = delete;

            /**
            * @brief Deleted move constructor
            */
            TimeManager(TimeManager&& manager) = delete;

        private:
            static TimeManager _instance;
            uint64_t _currentTick = -1;
            uint64_t _lastTick = -1;
            double _deltaTime = 0.0;
            double _timeScale = 1.0;
    };
}

#endif //SPIC_ENGINE_TIMEMANAGER_HPP
