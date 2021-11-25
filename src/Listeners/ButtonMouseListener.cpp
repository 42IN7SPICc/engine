#include "ButtonMouseListener.hpp"

#include "Input.hpp"

#include "../Utils/RectangleUtil.hpp"
#include "../Utils/ZoneUtil.hpp"

#include <cmath>

using namespace engine;
using namespace spic;

ButtonMouseListener::ButtonMouseListener(Button* button) : _button{button}
{
}

void ButtonMouseListener::OnMouseReleased()
{
    if (Input::GetMouseButtonUp(Input::MouseButton::LEFT))
    {
        if (_button != nullptr)
        {
            if (_button->Interactable() && _button->IsActiveInWorld())
            {
                auto transform = _button->AbsoluteTransform();
                auto width = _button->Width() * transform.scale;
                auto height = _button->Height() * transform.scale;
                auto mousePos = Input::MousePosition();

                if (transform.rotation == 0)
                {
                    auto hDiff = height * 0.5;
                    auto wDiff = width * 0.5;

                    auto top = transform.position.y - hDiff;
                    auto right = transform.position.x + wDiff;
                    auto bottom = transform.position.y + hDiff;
                    auto left = transform.position.x - wDiff;

                    if (mousePos.y >= top && mousePos.y <= bottom && mousePos.x >= left && mousePos.x <= right)
                    {
                        _button->Click();
                    }
                }
                else
                {
                    auto points = RectangleUtil::Rotate(transform.position, width, height, std::fmod(transform.rotation, 360));

                    if (ZoneUtil::InZone(mousePos, points))
                    {
                        _button->Click();
                    }
                }
            }
        }
    }
}
