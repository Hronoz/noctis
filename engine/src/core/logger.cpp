#include "core/logger.hpp"
#include <cstdio>
#include <cstdarg>

void log_message(LogLevel level, const char *msg, ...)
{
    const char *log_list[] = { "[INFO]:  ", "[WARN]:  ", "[ERROR]: " };
    va_list args;
    va_start(args, msg);
    char buf[1024];
    std::vsnprintf(buf, sizeof buf, msg, args);
    std::fprintf(stderr, "%s%s\n", log_list[static_cast<int>(level)], buf);
}