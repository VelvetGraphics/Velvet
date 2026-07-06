#pragma once
#include "Velvet/Common/CommonInclude.hpp"
#include "Velvet/Main/ApplicationState.hpp"
#include "Velvet/Main/Layer.hpp"

namespace Velvet {
    struct ApplicationCreateInfo
    {
        ApplicationState::State CreationState = ApplicationState::None;
        std::vector<Layer*> Layers;
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

    protected:
        Application(ApplicationCreateInfo&& createInfo);

    protected:
        AppState m_CurrentState = ApplicationState::None;

        std::vector<Layer*> m_Layers;

    private:
        static Application* Create();
        static void Destroy() { s_Instance = nullptr; }

        void Run();
        void Close() { m_Running = false; }

    private:
        inline static Application* s_Instance = nullptr;

        bool m_Running = true;

        friend class Main;
    };
} // namespace Velvet
