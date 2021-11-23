#include "InputManager.hpp"

#include <algorithm>

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
    int length = 0;
    const unsigned char* keysBuffer = SDL_GetKeyboardState(&length);

    _keysCurrent = {keysBuffer, keysBuffer + length};

    if (_mouseCurrent != 0)
    {
        for (const auto& listener: _mouseListeners) listener->OnMousePressed();
    }
}

void InputManager::HandleEvent(const SDL_Event& event)
{
    switch (event.type)
    {
        case SDL_MOUSEMOTION:
        {
            std::vector<spic::IMouseListener*> listeners = _mouseListeners;
            for (const auto& listener: listeners)
                listener->OnMouseMoved();
            break;
        }
        case SDL_MOUSEBUTTONDOWN:
        {
            std::vector<spic::IMouseListener*> listeners = _mouseListeners;
            for (const auto& listener: listeners)
                listener->OnMouseClicked();
            break;
        }
        case SDL_MOUSEBUTTONUP:
        {
            std::vector<spic::IMouseListener*> listeners = _mouseListeners;
            for (const auto& listener: listeners)
                listener->OnMouseReleased();
            break;
        }
        case SDL_KEYDOWN:
        {
            std::vector<spic::IKeyListener*> listeners = _keyListeners;
            for (const auto& listener: listeners)
                listener->OnKeyPressed();
            break;
        }
        case SDL_KEYUP:
        {
            std::vector<spic::IKeyListener*> listeners = _keyListeners;
            for (const auto& listener: listeners)
                listener->OnKeyReleased();
            break;
        }
    }
}

void InputManager::RegisterKeyListener(IKeyListener& listener)
{
    _keyListeners.push_back(&listener);
}

void InputManager::UnregisterKeyListener(IKeyListener& listener)
{
    auto iterator = std::find(_keyListeners.begin(), _keyListeners.end(), &listener);
    if (iterator != _keyListeners.end())
        _keyListeners.erase(iterator);
}

void InputManager::RegisterMouseListener(IMouseListener& listener)
{
    _mouseListeners.push_back(&listener);
}

void InputManager::UnregisterMouseListener(IMouseListener& listener)
{
    auto iterator = std::find(_mouseListeners.begin(), _mouseListeners.end(), &listener);
    if (iterator != _mouseListeners.end())
        _mouseListeners.erase(iterator);
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