#include "Main.hpp"

#include "Velvet/Main/Application.hpp"

namespace Velvet {
    void Main::Execute(int argc, char** argv)
    {
       bool start = true;

        while (start)
        {
            start = false;

            CreateContext();
            Application* Application = Application::Create(argc, argv, &start);
            Application->Run();
            Application::Destroy();
            DestroyContext();
        }
    }

    void Main::CreateContext()
    {
        // TODO: Assertions
        GlfwWindow::CreateContext();
    }

    void Main::DestroyContext()
    {
        GlfwWindow::DestroyContext();
    }
} // namespace Velvet

int main(int argc, char** argv) { Velvet::Main::Execute(argc, argv); }
