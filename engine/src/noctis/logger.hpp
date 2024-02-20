#pragma once

#include "noctis.hpp"

enum class LogLevel
{
    Info,
    Warn,
    Debug,
    Error,
};

void logMessage(LogLevel level, const char *msg, ...);

#ifndef NDEBUG // if debug
#define ERROR(msg, ...) logMessage(LogLevel::Error, msg __VA_OPT__(, ) __VA_ARGS__)
#define DEBUG(msg, ...) logMessage(LogLevel::Debug, msg __VA_OPT__(, ) __VA_ARGS__)
#else
#define Error(msg, ...)
#define Debug(msg, ...)
#endif
#define INFO(msg, ...) logMessage(LogLevel::Info, msg __VA_OPT__(, ) __VA_ARGS__)
#define WARN(msg, ...) logMessage(LogLevel::WARN, msg __VA_OPT__(, ) __VA_ARGS__)
