#pragma once

enum class LogLevel
{
    INFO,
    WARN,
    ERROR
};

void log_message(LogLevel level, const char *msg, ...);

#ifdef NDEBUG
#define ERROR(msg, ...)
#else
#define ERROR(msg, ...) log_message(LogLevel::ERROR, msg __VA_OPT__(,) __VA_ARGS__)
#endif
#define INFO(msg, ...) log_message(LogLevel::INFO, msg __VA_OPT__(,) __VA_ARGS__)
#define WARN(msg, ...) log_message(LogLevel::WARN, msg __VA_OPT__(,) __VA_ARGS__)
