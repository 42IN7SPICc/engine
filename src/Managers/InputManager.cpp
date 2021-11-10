#include "InputManager.hpp"

using namespace engine;
using namespace spic;

InputManager InputManager::_instance{};

InputManager::InputManager() : _mousePosition{new Point()} {
    for (int i = 0; i < SDL_NUM_SCANCODES; i++)
    {
        _keysCurrent[i] = false;
        _keysPrevious[i] = false;
    }
    _mouseCurrent[SDL_BUTTON_LEFT] = false;
    _mouseCurrent[SDL_BUTTON_MIDDLE] = false;
    _mouseCurrent[SDL_BUTTON_RIGHT] = false;
    _mouseCurrent[SDL_BUTTON_X1] = false;
    _mouseCurrent[SDL_BUTTON_X2] = false;
    _mousePrevious = {_mouseCurrent};
}

bool InputManager::AnyKeyDown() {
    for (const auto& key: _keysCurrent)
    {
        if (key.second && !_keysPrevious[key.first]) return true;
    }
    return false;
}

bool InputManager::AnyKey() const {
    for (const auto& key: _keysCurrent)
        if (key.second) return true;
    return false;
}

bool InputManager::KeyDown(const Input::KeyCode& keyCode) {
    auto key = ToKey(keyCode);
    if (_keysPrevious.empty()) return _keysCurrent[key];
    return _keysPrevious[key] && _keysCurrent[key];
}

bool InputManager::KeyFrameDown(const Input::KeyCode& keyCode) {
    auto key = ToKey(keyCode);
    if (_keysPrevious.empty()) return _keysCurrent[key];
    return !_keysPrevious[key] && _keysCurrent[key];
}

bool InputManager::KeyFrameUp(const Input::KeyCode& keyCode) {
    auto key = ToKey(keyCode);
    if (_keysPrevious.empty()) return false;
    return _keysPrevious[key] && !_keysCurrent[key];
}

bool InputManager::MouseDown(const Input::MouseButton& mouseButton) {
    auto mouse = ToKey(mouseButton);
    if (_mousePrevious.empty()) return _mouseCurrent[mouse];
    return _mousePrevious[mouse] && _mouseCurrent[mouse];
}

bool InputManager::MouseFrameDown(const Input::MouseButton& mouseButton) {
    auto mouse = ToKey(mouseButton);
    if (_mousePrevious.empty()) return _mouseCurrent[mouse];
    return !_mousePrevious[mouse] && _mouseCurrent[mouse];
}

bool InputManager::MouseFrameUp(const Input::MouseButton& mouseButton) {
    auto mouse = ToKey(mouseButton);
    if (_mousePrevious.empty()) return false;
    return _mousePrevious[mouse] && !_mouseCurrent[mouse];
}

const spic::Point& InputManager::MousePosition() const {
    return *_mousePosition;
}

void InputManager::HandleEvent(const SDL_Event& event) {
    switch (event.type)
    {
        case SDL_MOUSEMOTION:
        {
            _mousePosition->x = event.motion.x;
            _mousePosition->y = event.motion.y;
            for (const auto& listener: Input::_mouseListeners) listener->OnMouseMoved();
            break;
        }
        case SDL_MOUSEBUTTONDOWN:
        {
            _mousePrevious[event.button.button] = _mouseCurrent[event.button.button];
            _mouseCurrent[event.button.button] = true;
            for (const auto& listener: Input::_mouseListeners) listener->OnMouseClicked();
            break;
        }
        case SDL_MOUSEBUTTONUP:
        {
            _mousePrevious[event.button.button] = _mouseCurrent[event.button.button];
            _mouseCurrent[event.button.button] = false;
            for (const auto& listener: Input::_mouseListeners) listener->OnMouseReleased();
            break;
        }
        case SDL_KEYDOWN:
        {
            _keysPrevious[event.key.keysym.scancode] = _keysCurrent[event.key.keysym.scancode];
            _keysCurrent[event.key.keysym.scancode] = true;
            for (const auto& listener: Input::_keyListeners) listener->OnKeyPressed();
            break;
        }
        case SDL_KEYUP:
        {
            _keysPrevious[event.key.keysym.scancode] = _keysCurrent[event.key.keysym.scancode];
            _keysCurrent[event.key.keysym.scancode] = false;
            for (const auto& listener: Input::_keyListeners) listener->OnKeyReleased();
            break;
        }
    }
}

void InputManager::Update() {
    for (const auto& mouse: _mouseCurrent)
    {
        if (mouse.second)
        {
            for (const auto& listener: Input::_mouseListeners) listener->OnMousePressed();
            break;
        }
    }

    _keysPrevious = _keysCurrent;
}

InputManager& InputManager::GetInstance() {
    return _instance;
}

Uint8 InputManager::ToKey(const spic::Input::MouseButton& mouseButton) {
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

unsigned char InputManager::ToKey(const spic::Input::KeyCode& key) {
    return static_cast<char>(key);
}