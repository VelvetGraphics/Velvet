#include "Main.hpp"

#include "Velvet/Main/Application.hpp"

namespace Velvet {
    void Main::Execute()
    {
        // TODO: Restart

        Application* Application = Application::Create();
        Application->Run();
        Application::Destroy();
    }
} // namespace Velvet

int main(int argc, char** argv) { Velvet::Main::Execute(); }
