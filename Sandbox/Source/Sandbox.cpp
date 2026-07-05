#include "Velvet/Velvet.hpp"

class SandboxApplication : public Velvet::Application
{
public:
 SandboxApplication() : Application() {}
};

Velvet::Application* Velvet::Application::Create()
{
    s_Instance = new SandboxApplication();
    return s_Instance;
}
