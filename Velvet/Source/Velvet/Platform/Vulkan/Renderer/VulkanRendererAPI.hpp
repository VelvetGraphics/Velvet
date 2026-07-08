#pragma once
#include "Velvet/Renderer/RendererAPI.hpp"

namespace Velvet {
    class VulkanRendererAPI final : public RendererAPI
    {
    public:
        void Init() override;
    };
} // namespace Velvet
