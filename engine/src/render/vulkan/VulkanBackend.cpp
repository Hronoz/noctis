#include "VulkanBackend.hpp"

#include "noctis/logger.hpp"
#include <vulkan/vulkan.h>

static struct VulkanContext
{
    VkInstance instance;
    VkDevice device;
} context;

VulkanBackend::VulkanBackend(const char *appName)
{
    VkApplicationInfo applicationInfo = { VK_STRUCTURE_TYPE_APPLICATION_INFO };
    applicationInfo.apiVersion = VK_API_VERSION_1_2;
    applicationInfo.pApplicationName = appName;
    applicationInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    applicationInfo.pEngineName = "Noctis Engine";
    applicationInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);

    VkInstanceCreateInfo createInfo = { VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO };
    createInfo.pApplicationInfo = &applicationInfo;
    createInfo.enabledExtensionCount = 0;
    createInfo.ppEnabledExtensionNames = nullptr;
    createInfo.enabledLayerCount = 0;
    createInfo.ppEnabledLayerNames = nullptr;

    VkResult result = vkCreateInstance(&createInfo, nullptr, &context.instance);
    if (result != VK_SUCCESS) {
        ERROR("vkCreateInstance failed with result %u", result);
    }

    DEBUG("Vulkan renderer initialized successfully.");
}

void VulkanBackend::resized(u16 width, u16 height) {}

bool VulkanBackend::beginFrame()
{
    return false;
}

bool VulkanBackend::endFrame()
{
    return false;
}

VulkanBackend::~VulkanBackend() = default;
