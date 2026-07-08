#pragma once
#include "Velvet/Common/CommonInclude.hpp"

namespace Velvet {
    class Main final
    {
    public:
        static void Execute(const std::vector<std::string>& arguments);

    private:
        static void CreateContext(const std::vector<std::string>& arguments);
        static void DestroyContext();
    };
} // namespace Velvet
