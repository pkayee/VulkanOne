#pragma once

#include <vk_one/engine/renderer/renderer_pch.h>
#include <vk_one/engine/core/window.h>
#include <vk_one/engine/renderer/physical_device.hpp>

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
        #ifdef NDEBUG
          const bool enableValidationLayers = false;
        #else
          const bool enableValidationLayers = true;
        #endif

        PhysicalDevice(Window &window);
        ~PhysicalDevice();

        PhysicalDevice(const PhysicalDevice &) = delete;
        PhysicalDevice &operator=(const PhysicalDevice &) = delete;
        PhysicalDevice(const PhysicalDevice &&) = delete;
        PhysicalDevice &operator=(const PhysicalDevice &&) = delete;

        SwapChainSupportDetails getSwapChainSupportDetails() { return  querySwapchainSupport(PhysicalDevice); }
        QueueFamilyIndices findQueueFamilies();
        VkFormat findSupportedFormat(
            const std::vector<VkFormat> &candidates,
            VkImageTiling tiling,
            VkFormatFeatureFlags features
            );
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
        Window &m_window;
    };
}
