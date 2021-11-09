#include "Button.hpp"
#include "Input.hpp"

#include "../Listeners/ButtonMouseListener.hpp"

using namespace engine;
using namespace spic;

Button::Button(const std::string& name, const std::string& tag, int layer, double width, double height) : UIObject(name, tag, layer, width, height), _listener{nullptr, &Button::DestroyListener} {
    interactable = true;

    _listener.reset(new ButtonMouseListener{this});
    Input::RegisterMouseListener(*_listener);
}

void Button::DestroyListener(IMouseListener* listener) {
    Input::UnregisterMouseListener(*listener);
}