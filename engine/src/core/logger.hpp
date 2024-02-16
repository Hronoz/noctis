#pragma once

#include "noctis.hpp"

enum class LogLevel
{
    INFO,
    WARN,
    DEBUG,
    ERROR
};

void log_message(LogLevel level, const char *msg, ...);

#ifndef NDEBUG
#define ERROR(msg, ...) log_message(LogLevel::ERROR, msg __VA_OPT__(,) __VA_ARGS__)
#define DEBUG(msg, ...) log_message(LogLevel::DEBUG, msg __VA_OPT__(,) __VA_ARGS__)
#else
#define ERROR(msg, ...)
#define DEBUG(msg, ...)
#endif
#define INFO(msg, ...) log_message(LogLevel::INFO, msg __VA_OPT__(,) __VA_ARGS__)
#define WARN(msg, ...) log_message(LogLevel::WARN, msg __VA_OPT__(,) __VA_ARGS__)
