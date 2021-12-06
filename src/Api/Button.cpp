#include "Button.hpp"
#include "Input.hpp"

#include "../Listeners/ButtonMouseListener.hpp"

using namespace engine;
using namespace spic;

Button::Button(const std::string& name, const std::string& tag, int layer, double width, double height) : UIObject(name, tag, layer, width, height),
                                                                                                          _listener(new ButtonMouseListener(this), &Button::DestroyListener),
                                                                                                          onClick{[]() {}},
                                                                                                          interactable(true)
{
    Input::RegisterMouseListener(*_listener);
}

void Button::DestroyListener(IMouseListener* listener)
{
    Input::UnregisterMouseListener(*listener);
}

void Button::Click()
{
    onClick();
}

bool Button::Interactable() const
{
    return interactable;
}

void Button::Interactable(bool isInteractable)
{
    interactable = isInteractable;
}
