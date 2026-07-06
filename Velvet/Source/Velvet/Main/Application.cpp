#include "Application.hpp"

namespace Velvet {
    Application::Application(ApplicationCreateInfo&& createInfo) { m_Layers = std::move(createInfo.Layers); }

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
            for (Layer* layer : m_Layers)
                if (layer->MeetsRequirements())
                    layer->OnUpdate();
        }
    }

    void Application::PushLayer(Layer* layer)
    {
        layer->OnAttach();
        m_Layers.push_back(layer);
    }
} // namespace Velvet
