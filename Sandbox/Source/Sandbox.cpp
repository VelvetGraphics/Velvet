#include "Velvet/Velvet.hpp"

namespace SandboxState {
    enum State
    {
        SandboxState = 1 << Velvet::ApplicationState::Last,
    };
}

class SandboxLayer final : public Velvet::Layer
{
public:
    SandboxLayer() : Velvet::Layer("Sandbox Layer") {}

    void OnUpdate() override { std::cout << "Welcome to Velvet Engine!" << std::endl; }

    bool MeetsRequirements() override{ return (Velvet::Application::Instance()->GetState() & (U64)SandboxState::SandboxState) == SandboxState::SandboxState;}
};

class SandboxApplication final : public Velvet::Application
{
public:
    SandboxApplication(Velvet::ApplicationCreateInfo&& createInfo) : Application(std::move(createInfo))
    {
        m_CurrentState = (U64)Velvet::ApplicationState::Running | (U64)SandboxState::SandboxState;
    }

    ~SandboxApplication() override { m_CurrentState = Velvet::ApplicationState::Destroy; }
};

Velvet::Application* Velvet::Application::Create()
{
    Velvet::ApplicationCreateInfo createInfo = {};
    createInfo.CreationState = ApplicationState::Init;
    createInfo.Layers.push_back(new SandboxLayer);

    s_Instance = new SandboxApplication(std::move(createInfo));
    return s_Instance;
}
