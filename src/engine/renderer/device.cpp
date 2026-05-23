#include <vk_one/engine/renderer/device.hpp>
#include <vk_one/engine/renderer/constants.hpp>
#include <vk_one/engine/utils.hpp>
#include <set>

namespace vk_one {
    Device::Device(PhysicalDevice &physicalDevice) : m_physicalDevice(physicalDevice) {
        m_indices = m_physicalDevice.findQueueFamilies();
        createLogicalDevice();
        createCommandPool();
    }

    Device::~Device() {
        vkDestroyCommandPool(m_device, m_commandPool, nullptr);
        vkDestroyDevice(m_device, nullptr);
    }

    void Device::createLogicalDevice() {
        std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
        std::set<uint32_t> uniqueQueueFamilies = {
            m_indices.graphicsFamily,
            m_indices.presentFamily
        };

        float queuePriority = 1.0f;
        for (uint32_t queueFamily: uniqueQueueFamilies) {
            VkDeviceQueueCreateInfo queueCreateInfo{};
            queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
            queueCreateInfo.queueFamilyIndex = queueFamily;
            queueCreateInfo.queueCount = 1;
            queueCreateInfo.pQueuePriorities = &queuePriority;
            queueCreateInfos.push_back(queueCreateInfo);
        }

        VkPhysicalDeviceFeatures deviceFeatures{};
        deviceFeatures.samplerAnisotropy = VK_TRUE;

        VkDeviceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
        createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
        createInfo.pQueueCreateInfos = queueCreateInfos.data();
        createInfo.pEnabledFeatures = &deviceFeatures;
        createInfo.enabledExtensionCount = static_cast<uint32_t>(Constants::deviceExtensions.size());
        createInfo.ppEnabledExtensionNames = Constants::deviceExtensions.data();

        if (enableValidationLayers) {
            createInfo.enabledLayerCount = static_cast<uint32_t>(Constants::validationLayers.size());
            createInfo.ppEnabledLayerNames = Constants::validationLayers.data();
        } else {
            createInfo.enabledLayerCount = 0;
        }

        VK_CHECK_SUCCESS(
            vkCreateDevice(m_physicalDevice.handle(), &createInfo, nullptr, &m_device),
            "failed to create logical device!"
        );

        vkGetDeviceQueue(m_device, m_indices.graphicsFamily, 0, &m_graphicsQueue);
        vkGetDeviceQueue(m_device, m_indices.presentFamily, 0, &m_presentQueue);
    }

    void Device::createCommandPool() {
        VkCommandPoolCreateInfo poolInfo{};
        poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
        poolInfo.queueFamilyIndex = m_indices.graphicsFamily;
        poolInfo.flags =VK_COMMAND_POOL_CREATE_TRANSIENT_BIT | VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;

        VK_CHECK_SUCCESS(
            vkCreateCommandPool(m_device, &poolInfo, nullptr, &m_commandPool),
            "failed to create command pool!"
        );
    }
}
