#pragma once

#include <vk_one/engine/renderer/renderer_pch.h>
#include <vk_one/engine/renderer/physical_device.hpp>
#include <vk_one/engine/renderer/device.hpp>

namespace vk_one {
    class MemoryAllocator {
    public:
        MemoryAllocator(PhysicalDevice &physicalDevice, Device &device);
        ~MemoryAllocator();
        MemoryAllocator(const MemoryAllocator &) = delete;
        MemoryAllocator &operator=(const MemoryAllocator &) = delete;

        void createBuffer(VkDeviceSize size,
                          VkBufferUsageFlags usage,
                          VkMemoryPropertyFlags properties,
                          VkBuffer &buffer,
                          VkDeviceMemory &bufferMemory);

        void createImageWithInfo(const VkImageCreateInfo &imageInfo,
                                 VkMemoryPropertyFlags properties,
                                 VkImage &image,
                                 VkDeviceMemory &imageMemory);

        VkCommandBuffer beginSingleTimeCommands();
        void            endSingleTimeCommands(VkCommandBuffer commandBuffer);
        void            copyBuffer(VkBuffer src, VkBuffer dst, VkDeviceSize size);
        void            copyBufferToImage(VkBuffer buffer, VkImage image,
                                          uint32_t width, uint32_t height,
                                          uint32_t layerCount);

    private:
        uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);

        PhysicalDevice              &m_physicalDevice;
        Device                      &m_device;
        VkPhysicalDeviceMemoryProperties m_memProperties;
    };
}
