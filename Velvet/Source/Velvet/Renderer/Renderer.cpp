#include "Renderer.hpp"

#include "Velvet/Platform/Vulkan/Renderer/VulkanRendererAPI.hpp"

namespace Velvet {
    bool Renderer::Init(const std::vector<std::string>& arguments)
    {
        for (const std::string& arg : arguments)
        {
            if (arg == "-GraphicsAPI=None")
            {
                Logger::EngineError("No support for None (no) graphics API");
                return false;
            }

            if (arg == "-GraphicsAPI=Vulkan")
            {
                Logger::EngineInfo("Choosing the Vulkan graphics API");
#if VELVET_PLATFORM_USE_VULKAN
                s_API = new VulkanRendererAPI;
                break;
#else
                Logger::EngineError("Had -GraphicsAPI=Vulkan but Vulkan must not be used in this compiled version");
                return false;
#endif
            }
        }

        if (!s_API)
        {
            Logger::EngineError("Failed to initialized suiting renderer API (and graphics API). Did you forget to add "
                                "the -GraphicsAPI=... flag?");
            Logger::EngineInfo("The -GraphicsAPI flag can have the following parameters: 1: None, 2: Vulkan");
            return false;
        }

        s_API->Init();

        Logger::EngineTrace("Initialized Renderer");
        return true;
    }
} // namespace Velvet
