#pragma once
#include "Velvet/Common/CommonInclude.hpp"
#include "Velvet/Main/ApplicationState.hpp"
#include "Velvet/Main/Event.hpp"
#include "Velvet/Main/GlfwWindow.hpp"
#include "Velvet/Main/Layer.hpp"

namespace Velvet {
    struct ApplicationCreateInfo
    {
        ApplicationState::State CreationState = ApplicationState::None;
        bool* restart;
    };

    class Application
    {
    public:
        virtual ~Application();

        Application(const Application&) = delete;
        Application& operator=(const Application&) = delete;

        Application(Application&&) = delete;
        Application& operator=(Application&&) = delete;

        void PushLayer(Layer* layer);
        void PopLayer(Layer* layer);

        AppState GetState() const { return m_CurrentState; }

        static Application* Instance() { return s_Instance; }

        void Close() { m_Running = false; }
        void Restart() const
        {
            *m_ShouldRestart = true;
            s_Instance = nullptr;
        }

        EventBus& GetEventBus() { return m_EventBus; }
        void ForwardEvent(Scope<Event>&& e) { m_EventBus.Queue(std::move(e)); }

    protected:
        Application(ApplicationCreateInfo&& createInfo);

    protected:
        AppState m_CurrentState = ApplicationState::None;

        std::vector<Layer*> m_Layers;

        Ref<GlfwWindow> m_Window = nullptr;
        EventBus m_EventBus;

    private:
        static Application* Create(const std::vector<std::string>& arguments, bool* restart);
        static void Destroy() { s_Instance = nullptr; }

        void Run();

    private:
        inline static Application* s_Instance = nullptr;

        bool m_Running = true;
        bool* m_ShouldRestart = nullptr;

        friend class Main;
    };
} // namespace Velvet
