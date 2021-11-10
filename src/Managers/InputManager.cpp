#include "InputManager.hpp"

using namespace engine;
using namespace spic;

InputManager InputManager::_instance{};

InputManager::InputManager() : _mousePosition{new Point()}, _mousePrevious{0}, _mouseCurrent{0}
{
}

bool InputManager::AnyKeyDown()
{
    for (int i = 0; i < _keysCurrent.size(); ++i)
        if (_keysCurrent[i] == 1 && _keysPrevious[i] == 0) return true;
    return false;
}

bool InputManager::AnyKey() const
{
    for (auto key: _keysCurrent)
        if (key == 1) return true;
    return false;
}

bool InputManager::KeyDown(const Input::KeyCode& keyCode)
{
    auto key = ToKey(keyCode);
    if (_keysPrevious.empty()) return _keysCurrent[key] == 1;
    return _keysPrevious[key] == 1 && _keysCurrent[key] == 1;
}

bool InputManager::KeyFrameDown(const Input::KeyCode& keyCode)
{
    auto key = ToKey(keyCode);
    if (_keysPrevious.empty()) return _keysCurrent[key] == 1;
    return _keysPrevious[key] == 0 && _keysCurrent[key] == 1;
}

bool InputManager::KeyFrameUp(const Input::KeyCode& keyCode)
{
    auto key = ToKey(keyCode);
    if (_keysPrevious.empty()) return false;
    return _keysPrevious[key] == 1 && _keysCurrent[key] == 0;
}

bool InputManager::MouseDown(const Input::MouseButton& mouseButton) const
{
    auto mouse = ToKey(mouseButton);
    if (_mousePrevious == 0) return (_mouseCurrent & mouse) != 0;
    return (_mousePrevious & mouse) != 0 && (_mouseCurrent & mouse) != 0;
}

bool InputManager::MouseFrameDown(const Input::MouseButton& mouseButton) const
{
    auto mouse = ToKey(mouseButton);
    if (_mousePrevious == 0) return (_mouseCurrent & mouse) != 0;
    return (_mousePrevious & mouse) == 0 && (_mouseCurrent & mouse) != 0;
}

bool InputManager::MouseFrameUp(const Input::MouseButton& mouseButton) const
{
    auto mouse = ToKey(mouseButton);
    if (_mousePrevious == 0) return false;
    return (_mousePrevious & mouse) != 0 && (_mouseCurrent & mouse) == 0;
}

const spic::Point& InputManager::MousePosition() const
{
    return *_mousePosition;
}

void InputManager::Update()
{
    SDL_PumpEvents();

    int x, y;
    _mousePrevious = _mouseCurrent;
    _mouseCurrent = SDL_GetMouseState(&x, &y);

    _mousePosition->x = x;
    _mousePosition->y = y;

    _keysPrevious = std::move(_keysCurrent);
    int length;
    const unsigned char* keysBuffer = SDL_GetKeyboardState(&length);

    _keysCurrent = {keysBuffer, keysBuffer + length};

    if (_mouseCurrent != 0) {
        for (const auto& listener: Input::_mouseListeners) listener->OnMousePressed();
    }
}

void InputManager::HandleEvent(const SDL_Event& event)
{
    switch (event.type)
    {
        case SDL_MOUSEMOTION:
        {
            for (const auto& listener: Input::_mouseListeners) listener->OnMouseMoved();
            break;
        }
        case SDL_MOUSEBUTTONDOWN:
        {
            for (const auto& listener: Input::_mouseListeners) listener->OnMouseClicked();
            break;
        }
        case SDL_MOUSEBUTTONUP:
        {
            for (const auto& listener: Input::_mouseListeners) listener->OnMouseReleased();
            break;
        }
        case SDL_KEYDOWN:
        {
            for (const auto& listener: Input::_keyListeners) listener->OnKeyPressed();
            break;
        }
        case SDL_KEYUP:
        {
            for (const auto& listener: Input::_keyListeners) listener->OnKeyReleased();
            break;
        }
    }
}

InputManager& InputManager::GetInstance()
{
    return _instance;
}

Uint8 InputManager::ToKey(const spic::Input::MouseButton& mouseButton)
{
    switch (mouseButton)
    {
        case spic::Input::MouseButton::LEFT:
            return SDL_BUTTON_LEFT;
        case spic::Input::MouseButton::MIDDLE:
            return SDL_BUTTON_MIDDLE;
        case spic::Input::MouseButton::RIGHT:
            return SDL_BUTTON_RIGHT;
    }
    return 0;
}

unsigned char InputManager::ToKey(const spic::Input::KeyCode& key)
{
    return static_cast<char>(key);
}