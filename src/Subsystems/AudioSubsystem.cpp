#include "AudioSubsystem.hpp"

#include <AudioSource.hpp>
#include <GameObject.hpp>

#include "../Exceptions/SDLMixerException.hpp"
#include "../Managers/AudioManager.hpp"

#include <SDL_mixer.h>
#include <Engine.hpp>
#include <functional>

void engine::AudioSubsystem::Update()
{
    auto objects = spic::GameObject::All();
    auto currentScene = spic::Engine::Instance().PeekScene();
    if (_previousScene && _previousScene != currentScene)
    {
        for (const auto& gameObject: _previousScene->Contents())
        {
            auto found = std::find(objects.begin(), objects.end(), gameObject);
            if (found == objects.end())
            {
                for (const auto& audioSource: gameObject->GetComponents<spic::AudioSource>())
                {
                    if (audioSource->PlayingInScene)
                        audioSource->Stop();
                }
            }
        }
    }
    _previousScene = currentScene;

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

void engine::AudioSubsystem::PauseAllAudioPlayback()
{
    auto objects = spic::GameObject::All();

    for (const auto& object: objects)
    {
        auto audioSources = object->GetComponents<spic::AudioSource>();
        for (auto& audioSource: audioSources)
        {
            if (audioSource->Loop())
                audioSource->Pause();
            else
                audioSource->Stop();
            audioSource->PlayingInScene = false;
        }
    }
}

void engine::AudioSubsystem::StopAllAudioPlayback(const std::shared_ptr<spic::Scene>& scene)
{
    std::function<void(const std::vector<std::shared_ptr<spic::GameObject>>&)> recursiveLoop;
    recursiveLoop = [&recursiveLoop](const std::vector<std::shared_ptr<spic::GameObject>>& children) {
        for (const auto& item: children)
        {
            auto audioSources = item->GetComponents<spic::AudioSource>();
            for (auto& audioSource: audioSources)
            {
                audioSource->Stop();
                audioSource->PlayingInScene = false;
            }
            recursiveLoop(item->Children());
        }
    };

    recursiveLoop(scene->Contents());
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
