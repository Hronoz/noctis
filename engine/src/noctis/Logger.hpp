#pragma once

#include "noctis.hpp"

#ifndef NDEBUG // if debug
#define DEBUG(msg, ...) logMessage(LogLevel::Debug, msg __VA_OPT__(, ) __VA_ARGS__)
#else
#define DEBUG(msg, ...)
#endif
#define ERROR(msg, ...) logMessage(LogLevel::Error, msg __VA_OPT__(, ) __VA_ARGS__)
#define INFO(msg, ...) logMessage(LogLevel::Info, msg __VA_OPT__(, ) __VA_ARGS__)
#define WARN(msg, ...) logMessage(LogLevel::WARN, msg __VA_OPT__(, ) __VA_ARGS__)

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
} // namespace Noctis
