#include <GameObject.hpp>
#include <AudioSource.hpp>
#include "../Managers/AudioManager.hpp"

using namespace spic;

AudioSource::AudioSource(const std::string& audioClip, bool playOnAwake, bool looping, double volume) : audioClip(audioClip),
                                                                                                        playOnAwake(playOnAwake),
                                                                                                        loop(looping),
                                                                                                        volume(volume)
{
    if (playOnAwake)
        Play(looping);
}

void AudioSource::Play(bool looping)
{
    if (GameObject().expired()) return;
    auto parent = GameObject().lock();

    engine::AudioManager::GetInstance().Play(parent->Name(), audioClip, looping, volume);
}

void AudioSource::Stop()
{
    if (GameObject().expired()) return;
    auto parent = GameObject().lock();

    engine::AudioManager::GetInstance().Stop(parent->Name(), audioClip);
}

double AudioSource::Volume() const
{
    return volume;
}

void AudioSource::Volume(double newVolume)
{
    volume = newVolume;
}