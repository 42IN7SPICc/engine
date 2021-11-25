#ifndef SPIC_ENGINE_AUDIOMANAGER_HPP
#define SPIC_ENGINE_AUDIOMANAGER_HPP

#include <string>
#include <map>
#include <memory>
#include "../Models/AudioClip.hpp"

namespace engine
{
    class AudioManager
    {
        private:
            static AudioManager _instance;
            std::map<std::string, std::shared_ptr<AudioClip>> _audioClips = {};
            std::map<std::string, int> _channels = {};

            static void ChannelCallback(int channelNumber);

        public:
            AudioManager();

            void LoadAudioClip(const std::string& path);

            bool Contains(const std::string& path) const;

            void Play(const std::string& gameObjectName, const std::string& path, bool loop = false, double volume = 0.5);

            void Stop(const std::string& gameObjectName, const std::string& path);

            static AudioManager& GetInstance();
    };
}


#endif //SPIC_ENGINE_AUDIOMANAGER_HPP
