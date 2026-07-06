#include "Main.hpp"

#include "Velvet/Main/Application.hpp"

namespace Velvet {
    void Main::Execute(int argc, char** argv)
    {
        // TODO: Restart
        // TODO: pass argc and argv

        Application* Application = Application::Create();
        Application->Run();
        Application::Destroy();
    }
} // namespace Velvet

int main(int argc, char** argv) { Velvet::Main::Execute(argc, argv); }