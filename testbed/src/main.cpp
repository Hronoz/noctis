#include <core/logger.hpp>
#include <platform/platform.hpp>

int main()
{
    Platform platform;
    INFO("100");
    WARN("100");
    ERROR("100");
    platform.start("TEST TEST TEST", 100, 100, 1280, 720);

    return 0;
}