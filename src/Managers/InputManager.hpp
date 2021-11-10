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
    class InputManager
    {
        private:
            std::vector<unsigned char> _keysCurrent;
            std::vector<unsigned char> _keysPrevious;
            Uint32 _mouseCurrent;
            Uint32 _mousePrevious;
            std::unique_ptr<spic::Point> _mousePosition;
            static InputManager _instance;
        public:
            InputManager();

            bool AnyKeyDown();

            [[nodiscard]] bool AnyKey() const;

            bool KeyDown(const spic::Input::KeyCode& keyCode);

            bool KeyFrameDown(const spic::Input::KeyCode& keyCode);

            bool KeyFrameUp(const spic::Input::KeyCode& keyCode);

            [[nodiscard]] bool MouseDown(const spic::Input::MouseButton& button) const;

            [[nodiscard]] bool MouseFrameDown(const spic::Input::MouseButton& button) const;

            [[nodiscard]] bool MouseFrameUp(const spic::Input::MouseButton& button) const;

            [[nodiscard]] const spic::Point& MousePosition() const;

            void HandleEvent(const SDL_Event& event);

            void Update();

            static InputManager& GetInstance();

            static unsigned char ToKey(const spic::Input::KeyCode& key);

            static Uint8 ToKey(const spic::Input::MouseButton& button);
    };
}


#endif //SPIC_ENGINE_INPUTMANAGER_HPP
