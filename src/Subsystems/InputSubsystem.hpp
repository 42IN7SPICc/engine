#ifndef SPIC_ENGINE_INPUTSUBSYSTEM_HPP
#define SPIC_ENGINE_INPUTSUBSYSTEM_HPP

#include "ISubsystem.hpp"

namespace engine
{
    /**
     * @brief Subsystem to handle Input from the mouse and keyboard.
     */
    class InputSubsystem : public ISubsystem
    {
        public:
            /**
             * @brief Fetches changes in state from the providers and sends them to the InputManager.
             */
            void Update() override;
    };
}

#endif //SPIC_ENGINE_INPUTSUBSYSTEM_HPP
