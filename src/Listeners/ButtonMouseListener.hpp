#ifndef SPIC_ENGINE_BUTTONMOUSELISTENER_HPP
#define SPIC_ENGINE_BUTTONMOUSELISTENER_HPP

#include "Button.hpp"
#include "IMouseListener.hpp"

namespace engine
{
    /**
     * @brief An implementation of the mouse listener for buttons.
     */
    class ButtonMouseListener : public spic::IMouseListener
    {
        public:
            /**
             * @brief Constructor for the ButtonMouseListener.
             * @param button the button to send the event to.
             */
            explicit ButtonMouseListener(spic::Button* button);

            /**
             * @brief Triggers when the mouse is moved.
             */
            void OnMouseMoved() override
            {
            };

            /**
             * @brief Triggers when a mouse button has been clicked.
             */
            void OnMouseClicked() override
            {
            };

            /**
             * @brief Triggers when a mouse button has been pressed.
             */
            void OnMousePressed() override
            {
            };

            /**
             * @brief Triggers when a mouse button has been released.
             */
            void OnMouseReleased() override;

        private:
            spic::Button* _button;
    };
}

#endif //SPIC_ENGINE_BUTTONMOUSELISTENER_HPP
