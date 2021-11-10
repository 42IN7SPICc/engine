#include "RenderSubsystem.hpp"

#include "Engine.hpp"
#include "Sprite.hpp"
#include "GameObject.hpp"

using namespace spic;

engine::RenderSubsystem::RenderSubsystem() {
    auto &engine = Engine::Instance();
    auto &windowConfig = engine.Config().window;

    _window = std::make_unique<Window>(windowConfig.title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowConfig.width, windowConfig.height, windowConfig.fullscreen);
}

void engine::RenderSubsystem::Update() {
    Engine &engine = Engine::Engine::Instance();
    auto scene = engine.PeekScene();

    _window->Clear();

    for (std::shared_ptr<GameObject> gameObject: GameObject::All()) // NOLINT(performance-for-range-copy)
    {
        for (std::shared_ptr<Sprite> sprite: gameObject->GetComponents<Sprite>()) {
            if (sprite->Active()) {
                auto flip = static_cast<SDL_RendererFlip>(sprite->FlipX() && sprite->FlipY() ?
                                                          SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL :
                                                          sprite->FlipX() ?
                                                          SDL_FLIP_HORIZONTAL :
                                                          sprite->FlipY() ?
                                                          SDL_FLIP_VERTICAL :
                                                          SDL_FLIP_NONE);

                _window->Render(sprite->Texture(), gameObject->AbsoluteTransform(), flip);
            }
        }
    }

    _window->SwapBuffers();
}