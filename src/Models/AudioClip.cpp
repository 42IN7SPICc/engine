#include "AudioClip.hpp"

using namespace engine;

Mix_Chunk *AudioClip::Chunk() const {
    return _chunk.get();
}

AudioClip::AudioClip(Mix_Chunk *chunk) : _chunk(chunk, &Mix_FreeChunk) {

}