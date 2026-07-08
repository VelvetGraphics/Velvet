#if VELVET_PLATFORM_USE_GLFW

#include "GlfwWindow.hpp"

#include "Velvet/Main/Application.hpp"

#include <GLFW/glfw3.h>

#include "Velvet/Events/InputEvent.hpp"
#include "Velvet/Events/WindowEvent.hpp"

namespace Velvet {
    GlfwWindow::GlfwWindow(WindowProperties props)
    {
        m_Data.Width = props.Width;
        m_Data.Height = props.Height;
        m_Data.Title = std::move(props.Title);
        m_Data.Resizable = props.Resizable;

        m_Data.Self = this;

        // TODO: Bind fn macro instead of lambda
        m_Data.EventCallback = [](Scope<Event>&& e) -> void {
            if (Application* instance = Application::Instance())
                instance->ForwardEvent(std::move(e));
        };

        glfwWindowHint(GLFW_RESIZABLE, m_Data.Resizable);

        // TODO: Make renderer context (Switch here to set the GLFW API)
        m_Window = glfwCreateWindow(m_Data.Width, m_Data.Height, m_Data.Title.c_str(), nullptr, nullptr);
        glfwSetWindowUserPointer(m_Window, &m_Data);

        SetEventCallbacks();
    }

    GlfwWindow::~GlfwWindow()
    {
        if (m_Window)
            Close();
    }

    void GlfwWindow::Close()
    {
        glfwDestroyWindow(m_Window);
        m_Window = nullptr;
    }

    void GlfwWindow::PollEvents() { glfwPollEvents(); }

    void GlfwWindow::WaitEvents() { glfwWaitEvents(); }

    void GlfwWindow::CaptureMouse(bool enabled) const
    {
        glfwSetInputMode(m_Window, GLFW_CURSOR, enabled ? GLFW_CURSOR_HIDDEN : GLFW_CURSOR_NORMAL);
    }

    bool GlfwWindow::CreateContext()
    {
        static bool s_Initialized = false;
        if (!s_Initialized)
        {
            glfwInit();
            s_Initialized = true;
            return true;
        }

        return false;
    }

    void GlfwWindow::DestroyContext() { glfwTerminate(); }

    void GlfwWindow::SetEventCallbacks() const
    {
        glfwSetErrorCallback([](int err, const char* desc) {
            // TODO: Logging
            std::cout << "GLFW error " << err << ", Description: " << desc << std::endl;
        });

        glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
            WindowData* data = static_cast<WindowData*>(glfwGetWindowUserPointer(window));
            Key::Keycode keycode = static_cast<Key::Keycode>(key);

            switch (action)
            {
                case GLFW_PRESS:
                    data->EventCallback(Scope<KeyPressedEvent>::Create(keycode, false));
                    break;
                case GLFW_REPEAT:
                    data->EventCallback(Scope<KeyPressedEvent>::Create(keycode, true));
                    break;
                case GLFW_RELEASE:
                    data->EventCallback(Scope<KeyReleasedEvent>::Create(keycode));
                    break;
                default:
                    break;
            }
        });

        glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods) {
            WindowData* data = static_cast<WindowData*>(glfwGetWindowUserPointer(window));
            Mouse::Button mouseButton = static_cast<Mouse::Button>(button);

            switch (action)
            {
                case GLFW_PRESS:
                    data->EventCallback(Scope<MouseButtonPressedEvent>::Create(mouseButton, false));
                case GLFW_REPEAT:
                    data->EventCallback(Scope<MouseButtonPressedEvent>::Create(mouseButton, true));
                case GLFW_RELEASE:
                    data->EventCallback(Scope<MouseButtonReleasedEvent>::Create(mouseButton));
                default:
                    break;
            }
        });

        glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos) {
            WindowData* data = static_cast<WindowData*>(glfwGetWindowUserPointer(window));

            data->EventCallback(Scope<MouseMovedEvent>::Create(xPos, yPos));
        });

        glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset) {
            WindowData* data = static_cast<WindowData*>(glfwGetWindowUserPointer(window));

            data->EventCallback(Scope<MouseScrolledEvent>::Create(xOffset, yOffset));
        });

        glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window) {
            WindowData* data = static_cast<WindowData*>(glfwGetWindowUserPointer(window));

            data->EventCallback(Scope<WindowClosedEvent>::Create(data->Self));
        });

        glfwSetWindowPosCallback(m_Window, [](GLFWwindow* window, int xPos, int yPos) {
            WindowData* data = static_cast<WindowData*>(glfwGetWindowUserPointer(window));
            data->XPos = xPos;
            data->YPos = yPos;

            data->EventCallback(Scope<WindowMovedEvent>::Create(data->Self, xPos, yPos));
        });

        glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) {
            WindowData* data = static_cast<WindowData*>(glfwGetWindowUserPointer(window));
            data->Width = width;
            data->Height = height;

            data->EventCallback(Scope<WindowResizedEvent>::Create(data->Self, width, height));
        });

        glfwSetWindowFocusCallback(m_Window, [](GLFWwindow* window, int focused) {
            WindowData* data = static_cast<WindowData*>(glfwGetWindowUserPointer(window));

            if (focused)
                data->EventCallback(Scope<WindowFocusedEvent>::Create(data->Self));
            else
                data->EventCallback(Scope<WindowLostFocusedEvent>::Create(data->Self));
        });

        glfwSetWindowIconifyCallback(m_Window, [](GLFWwindow* window, int iconified) {
            WindowData* data = static_cast<WindowData*>(glfwGetWindowUserPointer(window));

            if (iconified)
                data->EventCallback(Scope<WindowMinimized>::Create(data->Self));
            else
                data->EventCallback(Scope<WindowUnMinimized>::Create(data->Self));
        });
    }
} // namespace Velvet

#endif
