#include "Application.hpp"

#include "Velvet/Events/WindowEvent.hpp"

namespace Velvet {
    Application::Application(ApplicationCreateInfo&& createInfo)
    {
        m_CurrentState = createInfo.CreationState;
        m_ShouldRestart = createInfo.restart;

        WindowProperties windowProps = {};
        windowProps.Width = 1280;
        windowProps.Height = 720;
        m_Window = Ref<GlfwWindow>::Create(windowProps);

        m_EventBus.Subscribe<WindowClosedEvent>([this](Event& e) -> void { Close(); });
    }

    Application::~Application()
    {
        for (Layer* layer : m_Layers)
        {
            layer->OnDetach();
            m_Layers.pop_back();
        }
    }

    void Application::Run()
    {
        while (m_Running)
        {
            // TODO: Fixed update

            for (Layer* layer : m_Layers)
                if (layer->MeetsRequirements())
                    layer->OnUpdate();

            GlfwWindow::PollEvents();
            m_EventBus.Dispatch();
        }
    }

    void Application::PushLayer(Layer* layer)
    {
        layer->OnAttach();
        m_Layers.push_back(layer);
    }

    void Application::PopLayer(Layer* layer)
    {
        layer->OnDetach();
        erase_if(m_Layers, [&](Layer* lyr) { return layer == lyr; });
    }
} // namespace Velvet
