#include "Velvet/Events/InputEvent.hpp"
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
    void OnkeyPressed(const Velvet::KeyPressedEvent& event) { std::cout <<"Key: "<< (char)event.GetKey() << std::endl; }
    SandboxLayer() : Velvet::Layer("Sandbox Layer") {}

    void OnAttach() override
    {
        Velvet::Application::Instance()->GetEventBus().Subscribe<Velvet::KeyPressedEvent>(
                [this](Velvet::Event& e) -> void {
                    Velvet::KeyPressedEvent event = static_cast<Velvet::KeyPressedEvent&>(e);
                    OnkeyPressed(event);
                });
    }

    void OnUpdate() override {}

    bool MeetsRequirements() override
    {
        return (Velvet::Application::Instance()->GetState() & (U64) SandboxState::SandboxState) ==
               SandboxState::SandboxState;
    }
};

class SandboxApplication final : public Velvet::Application
{
public:
    SandboxApplication(Velvet::ApplicationCreateInfo&& createInfo) : Application(std::move(createInfo))
    {
        m_CurrentState = (U64) Velvet::ApplicationState::Running | (U64) SandboxState::SandboxState;
    }

    ~SandboxApplication() override { m_CurrentState = Velvet::ApplicationState::Destroy; }
};

Velvet::Application* Velvet::Application::Create(const std::vector<std::string>& arguments, bool* restart)
{
    Velvet::ApplicationCreateInfo createInfo = {};
    createInfo.CreationState = ApplicationState::Init;
    createInfo.restart = restart;

    s_Instance = new SandboxApplication(std::move(createInfo));
    s_Instance->PushLayer(new SandboxLayer);
    return s_Instance;
}
