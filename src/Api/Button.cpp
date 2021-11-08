#include "Button.hpp"
#include "Input.hpp"

#include "../Listeners/ButtonMouseListener.hpp"

using namespace engine;
using namespace spic;

Button::Button(const std::string& name, const std::string& tag, int layer, double width, double height) : UIObject(name, tag, layer, width, height) {
    interactable = true;

    ButtonMouseListener listener{this};
    Input::RegisterMouseListener(listener);
}