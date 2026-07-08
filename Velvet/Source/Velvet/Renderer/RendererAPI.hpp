#pragma once

namespace Velvet {
    enum class GraphicsAPI
    {
        None = 0,
        Vulkan = 1,
    };

    class RendererAPI
    {
    public:
        virtual ~RendererAPI() = default;

        virtual void Init() = 0;

    protected:
        RendererAPI() = default;
    };
} // namespace Velvet
