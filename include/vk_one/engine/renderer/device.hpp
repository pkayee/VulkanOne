#pragma once

#include <vk_one/engine/renderer/pch.h>
#include <vk_one/engine/renderer/physical_device.hpp>

namespace vk_one {

    class Device {
    public:
        Device(PhysicalDevice &physicalDevice);
        ~Device();

        Device(const Device &) = delete;
        Device &operator=(const Device &) = delete;
        Device(const Device &&) = delete;
        Device &operator=(const Device &&) = delete;

        VkDevice      handle()        { return m_device; }
        VkCommandPool commandPool()   { return m_commandPool; }
        VkQueue       graphicsQueue() { return m_graphicsQueue; }
        VkQueue       presentQueue()  { return m_presentQueue; }
    private:
        void createLogicalDevice();
        void createCommandPool();

        VkDevice      m_device;
        VkCommandPool m_commandPool;
        VkQueue       m_graphicsQueue;
        VkQueue       m_presentQueue;

        PhysicalDevice &m_physicalDevice;
        QueueFamilyIndices m_indices;
    };
}
