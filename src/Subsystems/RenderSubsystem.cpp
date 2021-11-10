#include "RenderSubsystem.hpp"

#include "Engine.hpp"
#include "GameObject.hpp"
#include "Sprite.hpp"
#include "Text.hpp"

using namespace spic;

engine::RenderSubsystem::RenderSubsystem() {
    auto& engine = Engine::Instance();
    auto& windowConfig = engine.Config().window;

    _window = std::make_unique<Window>(windowConfig.title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowConfig.width, windowConfig.height, windowConfig.fullscreen);
}

void engine::RenderSubsystem::Update() {
    Engine& engine = Engine::Engine::Instance();
    auto scene = engine.PeekScene();

    _window->Clear();

    for (std::shared_ptr<GameObject> gameObject: GameObject::All()) // NOLINT(performance-for-range-copy)
    {
        auto transform = gameObject->AbsoluteTransform();
        for (std::shared_ptr<Sprite> sprite: gameObject->GetComponents<Sprite>()) {
            if (sprite->Active()) {
                auto flip = static_cast<SDL_RendererFlip>(sprite->FlipX() && sprite->FlipY() ?
                                                          SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL :
                                                          sprite->FlipX() ?
                                                          SDL_FLIP_HORIZONTAL :
                                                          sprite->FlipY() ?
                                                          SDL_FLIP_VERTICAL :
                                                          SDL_FLIP_NONE);

                _window->Render(sprite->Texture(), transform, flip);
            }
        }

        auto textObject = std::dynamic_pointer_cast<Text>(gameObject);
        if (textObject) {
            _window->RenderText(textObject->Content(), transform, textObject->Font(), textObject->Size(), textObject->TextAlignment(), textObject->TextColor(), textObject->Width());
        }
    }

    _window->SwapBuffers();
}