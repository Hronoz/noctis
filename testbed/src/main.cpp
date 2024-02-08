#include <core/logger.hpp>
#include <platform/platform.hpp>

int main()
{
    Platform platform("TEST TEST TEST", 100, 100, 1280, 720);
    INFO("test message");
    while (true) {
        if (platform.waitForEvent()) {
            break;
        }
    }

    return 0;
}