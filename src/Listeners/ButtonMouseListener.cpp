#include "ButtonMouseListener.hpp"

#include "Input.hpp"

#include "../Utils/RectangleUtil.hpp"
#include "../Utils/ZoneUtil.hpp"

using namespace engine;
using namespace spic;

ButtonMouseListener::ButtonMouseListener(Button* button) : _button{button} {
}

void ButtonMouseListener::OnMouseReleased() {
    if (Input::GetMouseButtonUp(Input::MouseButton::LEFT))
    {
        if (_button != nullptr)
        {
            if (_button->Interactable() && _button->IsActiveInWorld() && !_button->Parent().expired())
            {
                auto transform = _button->Parent().lock()->AbsoluteTransform();
                auto width = _button->Width() * transform.scale;
                auto height = _button->Height() * transform.scale;

                Point center{transform.position.x - (width / 2), transform.position.y - (height / 2)};

                auto points = RectangleUtil::Rotate(center, width, height, std::fmod(transform.rotation, 360));

                if (ZoneUtil::InZone(Input::MousePosition(), points))
                {
                    _button->Click();
                }
            }
        }
    }
}
