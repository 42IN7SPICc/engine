#include "Input.hpp"

#include "../Managers/InputManager.hpp"

#include <algorithm>

using namespace spic;
using namespace engine;

bool Input::AnyKey() {
    return InputManager::GetInstance().AnyKey();
}

bool Input::AnyKeyDown() {
    return InputManager::GetInstance().AnyKeyDown();
}

const Point Input::MousePosition() {
    return InputManager::GetInstance().MousePosition();
}

bool Input::GetKey(KeyCode key) {
    return InputManager::GetInstance().KeyDown(key);
}

bool Input::GetKeyDown(KeyCode key) {
    return InputManager::GetInstance().KeyFrameDown(key);
}

bool Input::GetKeyUp(KeyCode key) {
    return InputManager::GetInstance().KeyFrameUp(key);
}

bool Input::GetMouseButton(MouseButton which) {
    return InputManager::GetInstance().MouseDown(which);
}

bool Input::GetMouseButtonDown(MouseButton which) {
    return InputManager::GetInstance().MouseFrameDown(which);
}

bool Input::GetMouseButtonUp(MouseButton which) {
    return InputManager::GetInstance().MouseFrameUp(which);
}

void Input::RegisterKeyListener(IKeyListener& listener) {
    _keyListeners.push_back(&listener);
}

void Input::UnregisterKeyListener(IKeyListener& listener) {
    std::remove(_keyListeners.begin(), _keyListeners.end(), &listener);
}

void Input::RegisterMouseListener(IMouseListener& listener) {
    _mouseListeners.push_back(&listener);
}

void Input::UnregisterMouseListener(IMouseListener& listener) {
    std::remove(_mouseListeners.begin(), _mouseListeners.end(), &listener);
}