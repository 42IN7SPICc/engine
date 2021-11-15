#include "Animator.hpp"
#include "GameObject.hpp"

#include <utility>

using namespace spic;

Animator::Animator(int fps, const std::vector<std::shared_ptr<Sprite>>& sprites) : fps{fps},
                                                                                   _sprites{std::move(sprites)},
                                                                                   Playing{false},
                                                                                   Looping{false},
                                                                                   CurrentFrame{0},
                                                                                   FrameTime{0}
{
    FrameDuration = 1.0 / fps;
}

void Animator::ActivateFrame(int frameIndex)
{
    if (frameIndex >= 0 && frameIndex < Frames())
    {
        auto gameObject = GameObject();
        if (!gameObject.expired())
        {
            auto sprite = gameObject.lock()->GetComponent<Sprite>();
            if (sprite)
            {
                auto frameSprite = _sprites[frameIndex];

                sprite->Texture(frameSprite->Texture());
                sprite->Color(frameSprite->Color());
                sprite->FlipX(frameSprite->FlipX());
                sprite->FlipY(frameSprite->FlipY());
            }
        }
    }
}

int Animator::Frames()
{
    return _sprites.size();
}

int Animator::FPS() const
{
    return fps;
}

void Animator::FPS(int newFps)
{
    fps = newFps;
}

void Animator::Play(bool looping)
{
    Playing = true;
    Looping = looping;
}

void Animator::Stop()
{
    Playing = false;
}