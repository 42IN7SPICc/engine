#ifndef SPIC_ENGINE_AUDIOMANAGER_HPP
#define SPIC_ENGINE_AUDIOMANAGER_HPP

#include <string>
#include <map>
#include <memory>
#include "../Models/AudioClip.hpp"

namespace engine
{
    /**
     * @brief Caches multiple audio clips to prevent the Engine from accessing files multiple times.
     */
    class AudioManager
    {
        private:
            static AudioManager _instance;
            std::map<std::string, std::shared_ptr<AudioClip>> _audioClips = {};
            std::map<std::string, int> _channels = {};
        public:
            /**
             * @brief Triggers when a Channel has been finished and needs to be cleared.
             * @param channelNumber The number of the channel to be cleared.
             */
            static void ChannelCallback(int channelNumber);

            /**
             * @brief Load a AudioClip from the filesystem.
             * @param path The path to the audio file.
             */
            void LoadAudioClip(const std::string& path);

            /**
             * @brief Checks whether a AudioClip has been chached for a given file.
             * @param path The path to the audio file.
             * @return Whether there is a cache item for the path.
             */
            bool Contains(const std::string& path) const;

            /**
             * @brief Plays a AudioClip on a given GameObject.
             * @param gameObjectName The name of the GameObject.
             * @param path The path to the audio file.
             * @param loop Whether to play the AudioClip in a loop.
             * @param volume The volume to play the AudioClip at.
             */
            void Play(const std::string& gameObjectName, const std::string& path, bool loop = false, double volume = 0.5);

            /**
             * @brief Stops a AudioClip from playing at a given GameObject.
             * @param gameObjectName The name of the GameObject.
             * @param path The path to the audio file.
             */
            void Stop(const std::string& gameObjectName, const std::string& path);

            /**
             * @brief Stops a AudioClip from playing at a given GameObject.
             * @param gameObjectName The name of the GameObject.
             * @param path The path to the audio file.
             */
            void Pause(const std::string& gameObjectName, const std::string& path);

            /**
             * @brief Get the instance of the AudioManager.
             * @return The instance of the AudioManager.
             */
            static AudioManager& GetInstance();

            AudioManager() = default;

            AudioManager& operator=(const AudioManager& manager) = delete;

            AudioManager& operator=(AudioManager&& manager) = delete;

            AudioManager(const AudioManager& manager) = delete;

            AudioManager(AudioManager&& manager) = delete;
    };
}


#endif //SPIC_ENGINE_AUDIOMANAGER_HPP
