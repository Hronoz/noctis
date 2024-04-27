#include "Logger.hpp"

#include <cstdarg>
#include <cstdio>

namespace Noctis
{

    void logMessage(LogLevel level, const char *msg, ...)
    {
        const char *logList[] = {"[INFO]:  ", "[WARN]:  ", "[DEBUG]: ", "[ERROR]: "};
        va_list args;
        va_start(args, msg);
        char buf[1024];
        std::vsnprintf(buf, sizeof buf, msg, args);
        std::fprintf(stderr, "%s%s\n", logList[static_cast<int>(level)], buf);
    }
}  // namespace Noctis
