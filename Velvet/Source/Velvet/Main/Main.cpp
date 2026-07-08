#include "Main.hpp"

#include "Velvet/Main/Application.hpp"
#include "Velvet/Renderer/Renderer.hpp"

namespace Velvet {
    void Main::Execute(const std::vector<std::string>& arguments)
    {
        bool start = true;

        while (start)
        {
            start = false;

            CreateContext(arguments);
            Application* Application = Application::Create(arguments, &start);
            Application->Run();
            Application::Destroy();
            DestroyContext();
        }
    }

    void Main::CreateContext(const std::vector<std::string>& arguments)
    {
        Logger::Init();

        // FIXME: Make these run in distribution

        VELVET_ASSERT(Renderer::Init(arguments), "Failed to initialize Renderer");

#if VELVET_PLATFORM_USE_GLFW
        VELVET_ASSERT(GlfwWindow::CreateContext(), "Failed to Create GLFW context");
#endif
    }

    void Main::DestroyContext() { GlfwWindow::DestroyContext(); }
} // namespace Velvet

int main(int argc, char** argv)
{
    std::vector<std::string> argvVector(argc);
    for (U32 i = 0; i < argc; i++)
        argvVector[i] = argv[i];

    Velvet::Main::Execute(argvVector);
}
