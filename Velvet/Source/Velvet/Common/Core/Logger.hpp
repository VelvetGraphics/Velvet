#pragma once

#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

namespace Velvet {
    class Logger final
    {
    public:
        static void Init()
        {
            spdlog::set_pattern("%^[%T:%e] %n (%l) : %v%$", spdlog::pattern_time_type());

            s_CoreLogger = spdlog::stdout_color_mt("VELVET");
            s_CoreLogger->set_level(spdlog::level::trace);

            s_ClientLogger = spdlog::stdout_color_mt("APP");
            s_ClientLogger->set_level(spdlog::level::trace);

            s_CoreLogger->trace("Initialized logger");
        }

        template<typename... Args>
        static void EngineTrace(spdlog::format_string_t<Args...> format, Args&&... args)
        {
            s_CoreLogger->trace(format, std::forward<Args>(args)...);
        }

        template<typename... Args>
        static void EngineInfo(spdlog::format_string_t<Args...> format, Args&&... args)
        {
            s_CoreLogger->info(format, std::forward<Args>(args)...);
        }

        template<typename... Args>
        static void EngineWarn(spdlog::format_string_t<Args...> format, Args&&... args)
        {
            s_CoreLogger->warn(format, std::forward<Args>(args)...);
        }

        template<typename... Args>
        static void EngineError(spdlog::format_string_t<Args...> format, Args&&... args)
        {
            s_CoreLogger->error(format, std::forward<Args>(args)...);
        }

        template<typename... Args>
        static void Trace(spdlog::format_string_t<Args...> format, Args&&... args)
        {
            s_ClientLogger->trace(format, std::forward<Args>(args)...);
        }

        template<typename... Args>
        static void Info(spdlog::format_string_t<Args...> format, Args&&... args)
        {
            s_ClientLogger->info(format, std::forward<Args>(args)...);
        }

        template<typename... Args>
        static void Warn(spdlog::format_string_t<Args...> format, Args&&... args)
        {
            s_ClientLogger->warn(format, std::forward<Args>(args)...);
        }

        template<typename... Args>
        static void Error(spdlog::format_string_t<Args...> format, Args&&... args)
        {
            s_ClientLogger->error(format, std::forward<Args>(args)...);
        }

    private:
        inline static std::shared_ptr<spdlog::logger> s_CoreLogger = nullptr;
        inline static std::shared_ptr<spdlog::logger> s_ClientLogger = nullptr;
    };
} // namespace Velvet
