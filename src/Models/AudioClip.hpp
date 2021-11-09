#ifndef SPIC_ENGINE_AUDIOCLIP_HPP
#define SPIC_ENGINE_AUDIOCLIP_HPP


#include <memory>
#include "SDL_mixer.h"

namespace engine {
    class AudioClip {
    private:
        std::unique_ptr<Mix_Chunk, decltype(&Mix_FreeChunk)> _chunk;
    public:
        explicit AudioClip(Mix_Chunk *chunk);

        [[nodiscard]] Mix_Chunk *Chunk() const;
    };
}


#endif //SPIC_ENGINE_AUDIOCLIP_HPP
