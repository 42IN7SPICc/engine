#include "RenderSubsystem.hpp"

#include "Camera.hpp"
#include "Engine.hpp"
#include "GameObject.hpp"
#include "Sprite.hpp"
#include "Text.hpp"
#include "../Structs/DebugLines.hpp"

#include <algorithm>
#include <map>
#include <tuple>

using namespace spic;

engine::RenderSubsystem::RenderSubsystem(Window* window) : _window(window)
{
}

void engine::RenderSubsystem::Update()
{
    Engine& engine = Engine::Engine::Instance();
    auto scene = engine.PeekScene();

    std::shared_ptr<Camera> cameraObject;

    std::map<int, std::vector<std::shared_ptr<GameObject>>> objectLayers{};
    for (const auto& gameObject: GameObject::All())
    {
        int layer = gameObject->Layer();

        if (!cameraObject)
        {
            auto camera = std::dynamic_pointer_cast<Camera>(gameObject);
            if (camera)
                cameraObject = camera;
        }

        if (!objectLayers.contains(layer))
        {
            objectLayers.insert(std::make_pair(layer, std::vector<std::shared_ptr<GameObject>>{}));
        }
        objectLayers[layer].push_back(gameObject);
    }

    for (const auto& layer: objectLayers)
    {
        std::vector<std::shared_ptr<Sprite>> sprites{};
        for (const auto& gameObject: layer.second)
        {
            for (const auto& sprite: gameObject->GetComponents<Sprite>())
            {
                if (sprite->Active()) sprites.push_back(sprite);
            }
        }

        std::sort(sprites.begin(), sprites.end(), [](const std::shared_ptr<Sprite>& lhs, const std::shared_ptr<Sprite>& rhs) {
            int lSort = lhs->SortingLayer();
            int lOrder = lhs->OrderInLayer();
            int rSort = rhs->SortingLayer();
            int rOrder = rhs->OrderInLayer();

            return std::tie(lSort, lOrder) < std::tie(rSort, rOrder);
        });

        for (const auto& sprite: sprites)
        {
            auto flip = static_cast<SDL_RendererFlip>(sprite->FlipX() && sprite->FlipY() ? SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL : sprite->FlipX() ? SDL_FLIP_HORIZONTAL : sprite->FlipY() ? SDL_FLIP_VERTICAL : SDL_FLIP_NONE);

            _window->Render(sprite->Texture(), sprite->GameObject().lock()->AbsoluteTransform(), flip, sprite->Color());
        }

        for (const auto& gameObject: layer.second)
        {
            auto textObject = std::dynamic_pointer_cast<Text>(gameObject);
            if (textObject)
            {
                _window->RenderText(textObject->Content(), textObject->AbsoluteTransform(), textObject->Font(), textObject->Size(), textObject->TextAlignment(), textObject->TextColor(), textObject->Width());
            }
        }

        for (auto& line: engine::DebugLines::Lines())
        {
            _window->RenderLine(line.from.x, line.from.y, line.to.x, line.to.y, line.color);
        }

        engine::DebugLines::Clear();
    }
}