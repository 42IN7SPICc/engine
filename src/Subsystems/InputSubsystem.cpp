#include "Engine.hpp"

#include "InputSubsystem.hpp"
#include "../Managers/InputManager.hpp"

using namespace engine;
using namespace spic;

void InputSubsystem::Update() {
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_QUIT:
            {
                Engine::Instance().Shutdown();
                break;
            }
            case SDL_MOUSEMOTION:
            case SDL_MOUSEBUTTONDOWN:
            case SDL_MOUSEBUTTONUP:
            case SDL_KEYDOWN:
            case SDL_KEYUP:
            {
                InputManager::GetInstance().HandleEvent(event);
            }
        }
    }

    InputManager::GetInstance().Update();
}