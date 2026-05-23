#pragma once

#include <vk_one/engine/renderer/pch.h>
#include <vk_one/engine/renderer/instance.hpp>

namespace vk_one {
    struct QueueFamilyIndices {
        uint32_t graphicsFamily;
        uint32_t presentFamily;
        bool graphicsFamilyHasValue = false;
        bool presentFamilyHasValue = false;
        bool isComplete() { return graphicsFamilyHasValue && presentFamilyHasValue; }
    };

    struct SwapChainSupportDetails {
        VkSurfaceCapabilitiesKHR capabilities;
        std::vector<VkSurfaceFormatKHR> formats;
        std::vector<VkPresentModeKHR> presentModes;
    };

    class PhysicalDevice {
    public:
        PhysicalDevice(Instance &instance);

        ~PhysicalDevice();
        PhysicalDevice(const PhysicalDevice &) = delete;
        PhysicalDevice &operator=(const PhysicalDevice &) = delete;

        PhysicalDevice(const PhysicalDevice &&) = delete;
        PhysicalDevice &operator=(const PhysicalDevice &&) = delete;

        SwapChainSupportDetails getSwapChainSupportDetails() { return querySwapChainSupport(m_physicalDevice); }

        QueueFamilyIndices findQueueFamilies() { return findQueueFamilies(m_physicalDevice); }

        VkFormat findSupportedFormat(
            const std::vector<VkFormat> &candidates,
            VkImageTiling tiling,
            VkFormatFeatureFlags features
        );

        VkPhysicalDevice handle() { return m_physicalDevice; }
        VkPhysicalDeviceProperties properties;

    private:
        void pickPhysicalDevice();

        bool isDeviceSuitable(VkPhysicalDevice device);

        bool checkDeviceExtensionSupport(VkPhysicalDevice device);

        QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);

        SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);

        VkPhysicalDevice m_physicalDevice = VK_NULL_HANDLE;
        VkInstance m_instance;
        VkSurfaceKHR m_surface;
    };
}
