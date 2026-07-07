#pragma once

namespace Velvet {
    class Main final
    {
    public:
        static void Execute(int argc, char** argv);

    private:
        static void CreateContext();
        static void DestroyContext();
    };
} // namespace Velvet
