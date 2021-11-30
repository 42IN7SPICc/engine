#ifndef SPIC_ENGINE_INPUTMANAGER_HPP
#define SPIC_ENGINE_INPUTMANAGER_HPP

#include "Point.hpp"
#include "Input.hpp"
#include "IMouseListener.hpp"
#include "IKeyListener.hpp"

#include "SDL_stdinc.h"
#include "SDL_events.h"

#include <map>
#include <memory>
#include <vector>

namespace engine
{
    /**
     * @brief Handles all the input from the mouse and keyboard.
     */
    class InputManager
    {
        private:
            std::vector<unsigned char> _keysCurrent = {};
            std::vector<unsigned char> _keysPrevious = {};
            Uint32 _mouseCurrent = 0;
            Uint32 _mousePrevious = 0;
            std::unique_ptr<spic::Point> _mousePosition = {};
            std::vector<spic::IMouseListener*> _mouseListeners = {};
            std::vector<spic::IKeyListener*> _keyListeners = {};
            static InputManager _instance;
        public:
            /**
             * @brief Constructs a new instance of the InputManager
             */
            InputManager();

            /**
             * @brief Is any key or mouse button currently held down?
             */
            bool AnyKeyDown();

            /**
             * @brief Returns true the first frame the user hits any key or mouse button.
             */
            [[nodiscard]] bool AnyKey() const;

            /**
             * @brief Returns true while the user holds down the key identified by keycode.
             * @param keyCode The key code to check for.
             */
            bool KeyDown(const spic::Input::KeyCode& keyCode);

            /**
             * @brief Returns true during the frame the user starts pressing down the key identified by keycode.
             * @param keyCode The key code to check for.
             */
            bool KeyFrameDown(const spic::Input::KeyCode& keyCode);

            /**
             * @brief Returns true during the frame the user releases the key identified by keycode.
             * @param keyCode The key code to check for.
             */
            bool KeyFrameUp(const spic::Input::KeyCode& keyCode);

            /**
             * @brief Returns whether the given mouse button is held down.
             * @param button The mouse button to check for.
             */
            [[nodiscard]] bool MouseDown(const spic::Input::MouseButton& button) const;

            /**
             * @brief Returns true during the frame the user pressed the given mouse button.
             * @param button The mouse button to check for.
             */
            [[nodiscard]] bool MouseFrameDown(const spic::Input::MouseButton& button) const;

            /**
             * @brief Returns true during the frame the user releases the given mouse button.
             * @param button The mouse button to check for.
             */
            [[nodiscard]] bool MouseFrameUp(const spic::Input::MouseButton& button) const;

            /**
             * @brief The current mouse position in pixel coordinates.
             */
            [[nodiscard]] const spic::Point& MousePosition() const;

            /**
             * @brief Update the instance fields based on a given event.
             * @param event the given SDL Event.
             */
            void HandleEvent(const SDL_Event& event);

            /**
             * @brief Trigger a cleanup to remove old data en move current data to previous data.
             */
            void Update();

            /**
             * @brief Register a new key listener.
             * @param listener A reference to a key listener.
             */
            void RegisterKeyListener(spic::IKeyListener& listener);

            /**
             * @brief Unregister a key listener.
             * @param listener A reference to a key listener.
             */
            void UnregisterKeyListener(spic::IKeyListener& listener);

            /**
             * @brief Register a new mouse listener.
             * @param listener A reference to a mouse listener.
             */
            void RegisterMouseListener(spic::IMouseListener& listener);

            /**
             * @brief Unregister a mouse listener.
             * @param listener A reference to a mouse listener.
             */
            void UnregisterMouseListener(spic::IMouseListener& listener);

            /**
             * @brief Get the instance of the InputManager.
             * @return The instance of the InputManager.
             */
            static InputManager& GetInstance();

            /**
             * @brief Converts a key code to a char for SDL.
             * @param key The key code to be converted
             * @return The char matching the key code.
             */
            static unsigned char ToKey(const spic::Input::KeyCode& key);

            /**
             * @brief Converts a mouse button to a int for SDL.
             * @param button The mouse button to be converted.
             * @return The int matching the mouse button.
             */
            static Uint8 ToKey(const spic::Input::MouseButton& button);
    };
}


#endif //SPIC_ENGINE_INPUTMANAGER_HPP
