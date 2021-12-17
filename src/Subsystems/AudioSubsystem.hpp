#ifndef SPIC_ENGINE_AUDIOSUBSYSTEM_HPP
#define SPIC_ENGINE_AUDIOSUBSYSTEM_HPP

#include <memory>
#include <Scene.hpp>
#include "ISubsystem.hpp"

namespace engine
{
    /**
     * @brief Subsystem to handle AudioSource components.
     */
    class AudioSubsystem : public ISubsystem
    {
        private:
            std::shared_ptr<spic::Scene> _previousScene;

        public:
            /**
             * @brief Constructs a new instance of a AudioSubsystem.
             */
            AudioSubsystem();

            /**
            * @brief Pauses all audio playback for all AudioSource components currently playing.
            */
            static void PauseAllAudioPlayback();

            /**
             * @brief Stops all audio playback for all AudioSource components in the active scene.
             * @param scene to process audio components on
             */
            static void StopAllAudioPlayback(const std::shared_ptr<spic::Scene>& scene);

            /**
             * @brief Starts all AudioSource that need to be started during this update.
             */
            void Update() override;
    };
}

#endif //SPIC_ENGINE_AUDIOSUBSYSTEM_HPP
