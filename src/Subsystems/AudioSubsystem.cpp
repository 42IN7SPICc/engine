#include "AudioSubsystem.hpp"
#include "../Managers/AudioManager.hpp"
#include <AudioSource.hpp>
#include <GameObject.hpp>
#include <SDL_mixer.h>
#include <stdexcept>

void engine::AudioSubsystem::Update()
{
    auto objects = spic::GameObject::All();

    for (const auto& object: objects)
    {
        auto audioSources = object->GetComponents<spic::AudioSource>();
        for (auto& audioSource: audioSources)
        {
            if (audioSource->Active() && audioSource->PlayOnAwake() && !audioSource->PlayingInScene)
            {
                audioSource->Play(audioSource->Loop());
            }
            else if (!audioSource->Active() && audioSource->PlayingInScene)
            {
                audioSource->Stop();
            }
        }
    }
}

void engine::AudioSubsystem::StopAllAudioPlayback()
{
    auto objects = spic::GameObject::All(true);

    for (const auto& object: objects)
    {
        auto audioSources = object->GetComponents<spic::AudioSource>();
        for (auto& audioSource: audioSources)
        {
            audioSource->Stop();
            audioSource->PlayingInScene = false;
        }
    }
}

engine::AudioSubsystem::AudioSubsystem()
{
    int audioRate = 44100;
    Uint16 audioFormat = MIX_DEFAULT_FORMAT;
    int audioChannels = 2;
    int audioBuffers = 2048;

    if (Mix_OpenAudio(audioRate, audioFormat, audioChannels, audioBuffers) != 0)
        throw std::runtime_error("SDL_Mixer: Audio could not be initialised");

    Mix_ChannelFinished(&engine::AudioManager::ChannelCallback);
}
