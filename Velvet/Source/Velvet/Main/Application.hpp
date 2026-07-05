#pragma once

namespace Velvet {
    class Application
    {
    public:
        virtual ~Application() = default;

        Application(const Application&) = delete;
        Application& operator=(const Application&) = delete;

        Application(Application&&) = delete;
        Application& operator=(Application&&) = delete;

    protected:
        Application() = default;

    private:
        static Application* Create();
        static void Destroy() { s_Instance = nullptr; }

        void Run();

    private:
        inline static Application* s_Instance = nullptr;

        friend class Main;
    };
} // namespace Velvet
