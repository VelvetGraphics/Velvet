#pragma once
#include "Velvet/Main/Event.hpp"
#include "Velvet/Main/GlfwWindow.hpp"

namespace Velvet {
    class WindowEvent : public Event
    {
    public:
        virtual ~WindowEvent() override = default;

        EVENT_CATEGORY_FUNCTION(EventCategory::Window)

        // TODO: Make this an Observer type, so ownership is obvious
        /**
         * @brief Non-owning pointer to the window
         */
        GlfwWindow* Window = nullptr;

    protected:
        WindowEvent(GlfwWindow* window) : Window(window) {}
    };

    class WindowClosedEvent final : public WindowEvent
    {
    public:
        WindowClosedEvent(GlfwWindow* window) : WindowEvent(window) {}
        ~WindowClosedEvent() override = default;

        EVENT_TYPE_FUNCTIONS(EventType::WindowClosed)
    };

    class WindowMovedEvent final : public WindowEvent
    {
    public:
        WindowMovedEvent(GlfwWindow* window, int XPos, int YPos) : WindowEvent(window), m_XPos(XPos), m_YPos(YPos) {}
        ~WindowMovedEvent() override = default;

        int GetXPos() const { return m_XPos; }
        int GetYPos() const { return m_YPos; }

        EVENT_TYPE_FUNCTIONS(EventType::WindowMoved)

    private:
        int m_XPos = 0, m_YPos = 0;
    };

    class WindowResizedEvent final : public WindowEvent
    {
    public:
        WindowResizedEvent(GlfwWindow* window, int width, int height) :
            WindowEvent(window), m_Width(width), m_Height(height)
        {
        }

        ~WindowResizedEvent() override = default;

        int GetWidth() const { return m_Width; }
        int GetHeight() const { return m_Height; }

        EVENT_TYPE_FUNCTIONS(EventType::WindowResized)

    private:
        int m_Width = 0, m_Height = 0;
    };

    class WindowFocusedEvent final : public WindowEvent
    {
    public:
        WindowFocusedEvent(GlfwWindow* window) : WindowEvent(window) {}
        ~WindowFocusedEvent() override = default;

        EVENT_TYPE_FUNCTIONS(EventType::WindowFocused)
    };

    class WindowLostFocusedEvent final : public WindowEvent
    {
    public:
        WindowLostFocusedEvent(GlfwWindow* window) : WindowEvent(window) {}
        ~WindowLostFocusedEvent() override = default;

        EVENT_TYPE_FUNCTIONS(EventType::WindowLostFocus)
    };

    class WindowMinimized final : public WindowEvent
    {
    public:
        WindowMinimized(GlfwWindow* window) : WindowEvent(window) {}
        ~WindowMinimized() override = default;

        EVENT_TYPE_FUNCTIONS(EventType::WindowMinimized)
    };

    class WindowUnMinimized final : public WindowEvent
    {
    public:
        WindowUnMinimized(GlfwWindow* window) : WindowEvent(window) {}
        ~WindowUnMinimized() override = default;

        EVENT_TYPE_FUNCTIONS(EventType::WindowUnMinimized)
    };
} // namespace Velvet
