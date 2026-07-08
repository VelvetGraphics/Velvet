#pragma once

#define VELVET_EXIT_PROGRAM std::abort()

// TODO: Verify

#define VELVET_ASSERT(expr, ...)                                                                                       \
    do                                                                                                                 \
    {                                                                                                                  \
        if (!expr)                                                                                                     \
        {                                                                                                              \
            Velvet::Logger::Error("Assertion Failed with expression: {0}\n message: {1}\n\n file: {2},\n line: {3}",   \
                                  #expr, __VA_ARGS__, __FILE__, __LINE__);                                             \
        }                                                                                                              \
    } while (false)
