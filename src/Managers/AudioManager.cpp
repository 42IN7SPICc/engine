#include "AudioManager.hpp"

#include "Debug.hpp"

#include "../Exceptions/SDLMixerException.hpp"

#include <stdexcept>
#include <sstream>

#define MAX_VOLUME 0.6

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
        throw SDLMixerException("The Audio API could not load the audio file (" + path + ").");
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
    int channelNumber{-1};
    auto channel = _channels.find(channelName);
    if (channel != _channels.end())
    {
        channelNumber = channel->second;
    }

    if (channelNumber == -1)
    {
        channelNumber = Mix_PlayChannel(-1, _audioClips[path]->Chunk(), loop ? -1 : 0);
    }
    else if (Mix_Paused(channelNumber) > 0)
    {
        Mix_Resume(channelNumber);
    }


    if (channelNumber == -1)
    {
        std::stringstream ss{};
        ss << "Mix_PlayChannel ";
        ss << Mix_GetError();
        spic::Debug::LogError(ss.str());
        return;
    }

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

void AudioManager::Pause(const std::string& gameObjectName, const std::string& path)
{
    std::string channelName = getChannelName(gameObjectName, path);
    auto channel = _channels.find(channelName);
    if (channel == _channels.end()) return;

    int channelNumber = channel->second;
    Mix_Pause(channelNumber);
}

AudioManager& AudioManager::GetInstance()
{
    return _instance;
}

bool AudioManager::Contains(const std::string& path) const
{
    return _audioClips.count(path) > 0;
}

void AudioManager::ChannelCallback(int channelNumber)
{
    auto& audioManager = AudioManager::GetInstance();
    std::erase_if(audioManager._channels, [channelNumber](auto& item) {
        auto const&[key, value] = item;
        return value == channelNumber;
    });

    spic::Debug::Log(std::to_string(channelNumber) + " channel exited");
}