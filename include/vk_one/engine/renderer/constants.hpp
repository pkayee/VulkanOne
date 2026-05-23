#pragma once

#include <vk_one/engine/renderer/pch.h>

namespace vk_one {
    class Constants {
    public:
        static inline const std::vector<const char*> validationLayers = { "VK_LAYER_KHRONOS_validation" };
        static inline const std::vector<const char*> deviceExtensions = { VK_KHR_SWAPCHAIN_EXTENSION_NAME };
    };
}

