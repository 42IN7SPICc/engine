#ifndef SPIC_ENGINE_ANIMATORSUBSYSTEM_HPP
#define SPIC_ENGINE_ANIMATORSUBSYSTEM_HPP

#include "ISubsystem.hpp"

namespace engine
{
    /**
     * @brief Subsystem to handle Animator components.
     */
    class AnimatorSubsystem : public ISubsystem
    {
        public:
            /**
             * @brief Updates all the animators to their next frame when needed.
             */
            void Update() override;
    };
}

#endif //SPIC_ENGINE_ANIMATORSUBSYSTEM_HPP
