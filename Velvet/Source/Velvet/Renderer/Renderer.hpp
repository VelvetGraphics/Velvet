#pragma once
#include "Velvet/Common/CommonInclude.hpp"

#include "Velvet/Renderer/RendererAPI.hpp"

namespace Velvet {
    class Renderer final
    {
    public:
        static bool Init(const std::vector<std::string>& arguments);

    private:
        inline static RendererAPI* s_API = nullptr;
    };
} // namespace Velvet
