#pragma once

#include <vk_one/engine/renderer/renderer_pch.h>

namespace vk_one {
    inline void VK_CHECK_SUCCESS(VkResult result, const char* message) {
            if (result != VK_SUCCESS) {
                throw std::runtime_error(message);
            }
        }
    ;
}
