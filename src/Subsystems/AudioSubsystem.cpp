#include "AudioSubsystem.hpp"
#include <AudioSource.hpp>
#include <GameObject.hpp>

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
