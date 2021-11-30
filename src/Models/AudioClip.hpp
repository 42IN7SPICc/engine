#ifndef SPIC_ENGINE_AUDIOCLIP_HPP
#define SPIC_ENGINE_AUDIOCLIP_HPP


#include <memory>
#include "SDL_mixer.h"

namespace engine
{
    /**
     * @brief Stores a SDL Mixer Chunk to prevent memory leaks upon shutdown.
     */
    class AudioClip
    {
        private:
            std::unique_ptr<Mix_Chunk, decltype(&Mix_FreeChunk)> _chunk;
        public:
            /**
             * @brief Constructs a new AudioClip with a given chunk.
             * @param chunk The SDL Mixer Chunk to store.
             */
            explicit AudioClip(Mix_Chunk* chunk);

            /**
             * @brief Access the Mixer Chunk inside the model.
             * @return The chunk that is stored.
             */
            [[nodiscard]] Mix_Chunk* Chunk() const;
    };
}


#endif //SPIC_ENGINE_AUDIOCLIP_HPP
