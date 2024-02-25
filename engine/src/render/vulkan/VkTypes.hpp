#pragma once

#include "noctis/logger.hpp"
#include <vulkan/vk_enum_string_helper.h>

#define VK_CHECK(x)                                                                                                    \
    do {                                                                                                               \
        VkResult err = x;                                                                                              \
        if (err) {                                                                                                     \
            ERROR("Detected Vulkan error: %s", string_VkResult(err));                                                  \
            exit(err);                                                                                                 \
        }                                                                                                              \
    } while (0)