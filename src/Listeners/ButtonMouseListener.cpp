#include "ButtonMouseListener.hpp"

#include "Input.hpp"

#include "../Utils/RectangleUtil.hpp"
#include "../Utils/ZoneUtil.hpp"

#include <cmath>

using namespace engine;
using namespace spic;

ButtonMouseListener::ButtonMouseListener(Button* button) : _button{button} {
}

void ButtonMouseListener::OnMouseReleased() {
    if (Input::GetMouseButtonUp(Input::MouseButton::LEFT))
    {
        if (_button != nullptr)
        {
            if (_button->Interactable() && _button->IsActiveInWorld())
            {
                auto transform = _button->AbsoluteTransform();
                auto width = _button->Width() * transform.scale;
                auto height = _button->Height() * transform.scale;

                auto points = RectangleUtil::Rotate(transform.position, width, height, std::fmod(transform.rotation, 360));

                if (ZoneUtil::InZone(Input::MousePosition(), points))
                {
                    _button->Click();
                }
            }
        }
    }
}
