#pragma once
#include "Velvet/Main/Event.hpp"
#include "Velvet/Main/InputCodes.hpp"

namespace Velvet {
    class KeyEvent : public Event
    {
    public:
        KeyEvent(Key::Keycode keycode) : m_Key(keycode) {};
        virtual ~KeyEvent() override = default;

        Key::Keycode GetKey() const { return m_Key; }

        EVENT_CATEGORY_FUNCTION(EventCategory::Input)

    private:
        Key::Keycode m_Key;
    };

    class KeyPressedEvent final : public KeyEvent
    {
    public:
        KeyPressedEvent(Key::Keycode key, bool repeat) : KeyEvent(key), m_Repeat(repeat) {}
        ~KeyPressedEvent() override = default;

        bool IsRepeat() const { return m_Repeat; }

        EVENT_TYPE_FUNCTIONS(EventType::KeyPressed)

    private:
        bool m_Repeat;
    };

    class KeyReleasedEvent final : public KeyEvent
    {
    public:
        KeyReleasedEvent(Key::Keycode key) : KeyEvent(key) {}
        ~KeyReleasedEvent() override = default;

        EVENT_TYPE_FUNCTIONS(EventType::KeyReleased)
    };

    class MouseButtonPressedEvent final : public Event
    {
    public:
        MouseButtonPressedEvent(Mouse::Button button, bool repeat) : m_Button(button), m_Repeat(repeat) {}
        ~MouseButtonPressedEvent() override = default;

        Mouse::Button GetButton() const { return m_Button; }
        bool IsRepeat() const { return m_Repeat; }

        EVENT_CATEGORY_FUNCTION(EventCategory::Input)
        EVENT_TYPE_FUNCTIONS(EventType::MouseButtonPressed)

    private:
        Mouse::Button m_Button;
        bool m_Repeat;
    };

    class MouseButtonReleasedEvent final : public Event
    {
    public:
        MouseButtonReleasedEvent(Mouse::Button button) : m_Button(button) {}
        ~MouseButtonReleasedEvent() override = default;

        Mouse::Button GetButton() const { return m_Button; }

        EVENT_CATEGORY_FUNCTION(EventCategory::Input)
        EVENT_TYPE_FUNCTIONS(EventType::MouseButtonReleased)

    private:
        Mouse::Button m_Button;
    };

    class MouseMovedEvent final : public Event
    {
    public:
        MouseMovedEvent(int xPos, int yPos) : m_XOffset(xPos), m_YOffset(yPos) {}
        ~MouseMovedEvent() override = default;

        EVENT_CATEGORY_FUNCTION(EventCategory::Input)
        EVENT_TYPE_FUNCTIONS(EventType::MouseMoved)

    private:
        int m_XOffset = 0, m_YOffset = 0;
    };

    class MouseScrolledEvent final : public Event
    {
    public:
        MouseScrolledEvent(int xOffset, int yOffset) : m_XOffset(xOffset), m_YOffset(yOffset) {}
        ~MouseScrolledEvent() override = default;

        EVENT_CATEGORY_FUNCTION(EventCategory::Input)
        EVENT_TYPE_FUNCTIONS(EventType::MouseMoved)

    private:
        int m_XOffset = 0, m_YOffset = 0;
    };
} // namespace Velvet
