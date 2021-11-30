#ifndef SPIC_ENGINE_ISUBSYSTEM_HPP
#define SPIC_ENGINE_ISUBSYSTEM_HPP

namespace engine
{
    /**
     * @brief Interface for subsystems.
     */
    class ISubsystem
    {
        public:
            /**
             * @brief Triggers every frame to handles changes.
             */
            virtual void Update() = 0;
    };
}

#endif //SPIC_ENGINE_ISUBSYSTEM_HPP
