#pragma once

#include "noctis.hpp"

#ifdef NDEBUG
#define DEBUG(msg, ...)
#else
#define DEBUG(msg, ...) logMessage(LogLevel::Debug, msg __VA_OPT__(, ) __VA_ARGS__)
#endif
#define ERROR(msg, ...) logMessage(LogLevel::Error, msg __VA_OPT__(, ) __VA_ARGS__)
#define INFO(msg, ...) logMessage(LogLevel::Info, msg __VA_OPT__(, ) __VA_ARGS__)
#define WARN(msg, ...) logMessage(LogLevel::Warn, msg __VA_OPT__(, ) __VA_ARGS__)

namespace Noctis
{
    enum class LogLevel
    {
        Info,
        Warn,
        Debug,
        Error,
    };

    void logMessage(LogLevel level, const char *msg, ...);
}  // namespace Noctis
