#include "InputManager.hpp"

using namespace engine;
using namespace spic;

InputManager InputManager::_instance{};

InputManager::InputManager() : _mousePosition{new Point()} {
}

bool InputManager::AnyKeyDown() {
    for (const auto& item: _keysCurrent)
    {
        if (item.second && !_keysPrevious[item.first]) return true;
    }
    return false;
}

bool InputManager::AnyKey() const {
    for (const auto& item: _keysCurrent)
        if (item.second) return true;
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

            for (const auto& item: Input::_mouseListeners) item->OnMouseMoved();
        }
        case SDL_MOUSEBUTTONDOWN:
        {
            _mouseCurrent[event.button.button] = true;
            for (const auto& item: Input::_mouseListeners) item->OnMouseClicked();
        }
        case SDL_MOUSEBUTTONUP:
        {
            _mouseCurrent[event.button.button] = false;
            for (const auto& item: Input::_mouseListeners) item->OnMouseReleased();
        }
        case SDL_KEYDOWN:
        {
            _keysCurrent[event.key.keysym.scancode] = true;
            for (const auto& item: Input::_keyListeners) item->OnKeyPressed();
        }
        case SDL_KEYUP:
        {
            _keysCurrent[event.key.keysym.scancode] = false;
            for (const auto& item: Input::_keyListeners) item->OnKeyReleased();
        }
    }
}

void InputManager::Update() {
    for (const auto& item: _mouseCurrent)
    {
        if (item.second)
        {
            for (const auto& item: Input::_mouseListeners) item->OnMousePressed();
            break;
        }
    }

    _mousePrevious = {_mouseCurrent};
    _keysPrevious = {_keysCurrent};
}

InputManager& InputManager::GetInstance() {
    return _instance;
}

Uint8 InputManager::ToKey(const spic::Input::MouseButton& mouseButton) {
    switch (mouseButton)
    {
        case spic::Input::MouseButton::LEFT:
            return SDL_BUTTON_LMASK;
        case spic::Input::MouseButton::MIDDLE:
            return SDL_BUTTON_MMASK;
        case spic::Input::MouseButton::RIGHT:
            return SDL_BUTTON_RMASK;
    }
    return 0;
}

unsigned char InputManager::ToKey(const spic::Input::KeyCode& key) {
    return static_cast<char>(key);
}