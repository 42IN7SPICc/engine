#include <GameObject.hpp>
#include <AudioSource.hpp>
#include "../Managers/AudioManager.hpp"

using namespace spic;

AudioSource::AudioSource(const std::string& audioClip, bool playOnAwake, bool looping, double volume) : audioClip(audioClip),
                                                                                                        playOnAwake(playOnAwake),
                                                                                                        loop(looping),
                                                                                                        volume(volume),
                                                                                                        PlayingInScene(false)
{
}

void AudioSource::Play(bool looping)
{
    if (GameObject().expired()) return;
    auto parent = GameObject().lock();

    engine::AudioManager::GetInstance().Play(parent->Name(), audioClip, looping, volume);
    PlayingInScene = true;
}

void AudioSource::Stop()
{
    if (GameObject().expired()) return;
    auto parent = GameObject().lock();

    engine::AudioManager::GetInstance().Stop(parent->Name(), audioClip);
    PlayingInScene = false;
}

double AudioSource::Volume() const
{
    return volume;
}

void AudioSource::Volume(double newVolume)
{
    volume = newVolume;
}

bool AudioSource::Loop() const
{
    return loop;
}

bool AudioSource::PlayOnAwake() const
{
    return playOnAwake;
}
