#include "AudioSubsystem.hpp"

#include <AudioSource.hpp>
#include <GameObject.hpp>

#include "../Exceptions/SDLMixerException.hpp"
#include "../Managers/AudioManager.hpp"

#include <SDL_mixer.h>

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
                audioSource->PlayingInScene = true;
            }
            else if (!audioSource->Active() && audioSource->PlayingInScene)
            {
                audioSource->Stop();
                audioSource->PlayingInScene = false;
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

void engine::AudioSubsystem::PauseAllAudioPlayback()
{
    auto objects = spic::GameObject::All();

    for (const auto& object: objects)
    {
        auto audioSources = object->GetComponents<spic::AudioSource>();
        for (auto& audioSource: audioSources)
        {
            audioSource->Pause();
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
        throw SDLMixerException("The Audio API could not be initialized.");

    Mix_ChannelFinished(&engine::AudioManager::ChannelCallback);
}
