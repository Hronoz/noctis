#include "noctis.hpp"

#include <vulkan/vulkan.h>

#include "noctis/Logger.hpp"

namespace Noctis
{
    void test()
    {
        u32 extensionCount = 0;
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
        DEBUG("%d extensions supported", extensionCount);
    }
}  // namespace Noctis
