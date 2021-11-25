#include <stdexcept>
#include "AudioManager.hpp"
#include "Debug.hpp"

#define MAX_VOLUME 0.75

using namespace engine;

AudioManager engine::AudioManager::_instance{};

std::string getChannelName(const std::string& gameObjectName, const std::string& path)
{
    return gameObjectName + "%^&%" + path;
}

void AudioManager::LoadAudioClip(const std::string& path)
{
    Mix_Chunk* chunk = Mix_LoadWAV(path.c_str());
    if (chunk == nullptr)
    {
        throw std::runtime_error("SDL_Mixer: Audio file could not be loaded");
    }

    auto audioClip = std::make_shared<AudioClip>(chunk);
    _audioClips[path] = audioClip;
}

void AudioManager::Play(const std::string& gameObjectName, const std::string& path, bool loop, double volume)
{
    if (!Contains(path))
        LoadAudioClip(path);

    if (MAX_VOLUME < volume)
        volume = MAX_VOLUME;

    std::string channelName = getChannelName(gameObjectName, path);
    int channelNumber = Mix_PlayChannel(-1, _audioClips[path]->Chunk(), loop ? -1 : 0);

    Mix_Volume(channelNumber, (int) (128 * volume));

    _channels.insert_or_assign(channelName, channelNumber);
}

void AudioManager::Stop(const std::string& gameObjectName, const std::string& path)
{
    std::string channelName = getChannelName(gameObjectName, path);
    auto channel = _channels.find(channelName);
    if (channel == _channels.end()) return;

    int channelNumber = channel->second;
    Mix_HaltChannel(channelNumber);
}

AudioManager& AudioManager::GetInstance()
{
    return _instance;
}

bool AudioManager::Contains(const std::string& path) const
{
    return _audioClips.count(path) > 0;
}

AudioManager::AudioManager()
{
    int audioRate = 44100;
    Uint16 audioFormat = MIX_DEFAULT_FORMAT;
    int audioChannels = 2;
    int audioBuffers = 2048;

    if (Mix_OpenAudio(audioRate, audioFormat, audioChannels, audioBuffers) != 0)
        throw std::runtime_error("SDL_Mixer: Audio could not be initialised");

    Mix_ChannelFinished(&ChannelCallback);
}

void AudioManager::ChannelCallback(int channelNumber)
{
    auto audioManager = AudioManager::GetInstance();
    std::erase_if(audioManager._channels, [channelNumber](auto& item) {
        auto const&[key, value] = item;
        return value == channelNumber;
    });

    spic::Debug::Log(std::to_string(channelNumber) + " channel exited");
}