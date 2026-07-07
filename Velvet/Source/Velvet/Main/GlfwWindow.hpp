#pragma once
#include "GLFW/glfw3.h"
#include "Velvet/Common/CommonInclude.hpp"
#include "Velvet/Main/Event.hpp"

struct GLFWwindow;

namespace Velvet {
    struct WindowProperties
    {
        int Width = 0, Height = 0;
        int XPos = 0, YPos = 0;
        std::string Title;

        bool Resizable = false;
    };

    class GlfwWindow : public RefCounted
    {
    public:
        GlfwWindow(WindowProperties props);
        ~GlfwWindow();

        GlfwWindow(const GlfwWindow&) = delete;
        GlfwWindow& operator=(const GlfwWindow&) = delete;

        GlfwWindow(GlfwWindow&&) = default;
        GlfwWindow& operator=(GlfwWindow&&) = default;

        void Close();

        static void PollEvents();
        static void WaitEvents();

        void CaptureMouse(bool enabled) const;

        static bool CreateContext();
        static void DestroyContext();

    private:
        void SetEventCallbacks() const;
    private:
        struct WindowData
        {
            int Width = 0, Height = 0;
            int XPos = 0, YPos = 0;
            std::string Title;

            bool Resizable = false;

            GlfwWindow* Self = nullptr;

            bool Focused = true;
            bool Minimized = false;

            std::function<void(Scope<Event>&&)> EventCallback = nullptr;
        } m_Data;


        GLFWwindow* m_Window = nullptr;
    };
} // namespace Velvet
