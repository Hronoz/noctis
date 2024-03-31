#include "noctis.hpp"
#include "noctis/Logger.hpp"
#include <vulkan/vulkan.h>

namespace Noctis
{
    void test()
    {
        u32 extensionCount = 0;
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
        DEBUG("%d extensions supported", extensionCount);
    }
} // namespace