#ifndef SPIC_ENGINE_BUTTONMOUSELISTENER_HPP
#define SPIC_ENGINE_BUTTONMOUSELISTENER_HPP

#include "Button.hpp"
#include "IMouseListener.hpp"

namespace engine {
    class ButtonMouseListener : spic::IMouseListener {
    public:
        explicit ButtonMouseListener(spic::Button* button);

        void OnMouseMoved() override {};

        void OnMouseClicked() override {};

        void OnMousePressed() override {};

        void OnMouseReleased() override;

    private:
        spic::Button* _button;
    };
}

#endif //SPIC_ENGINE_BUTTONMOUSELISTENER_HPP
