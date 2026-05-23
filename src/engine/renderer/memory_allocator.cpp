#include <vk_one/engine/renderer/memory_allocator.hpp>

namespace vk_one {
    MemoryAllocator::MemoryAllocator(PhysicalDevice &physicalDevice, Device &device)
        : m_physicalDevice(physicalDevice), m_device(device) {
        vkGetPhysicalDeviceMemoryProperties(m_physicalDevice.handle(), &m_memProperties);
    }

    MemoryAllocator::~MemoryAllocator() {}

    uint32_t MemoryAllocator::findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties) {
        for (uint32_t i = 0; i < m_memProperties.memoryTypeCount; i++) {
            if ((typeFilter & (1 << i)) &&
                (m_memProperties.memoryTypes[i].propertyFlags & properties) == properties)

                return i;
        }
        Log::throwRuntimeError("Failed to find suitable memory type!");
        std::unreachable();
    }

    void MemoryAllocator::createBuffer(
        VkDeviceSize size,
        VkBufferUsageFlags usage,
        VkMemoryPropertyFlags properties,
        VkBuffer &buffer,
        VkDeviceMemory &bufferMemory) {
        VkBufferCreateInfo bufferInfo{};
        bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
        bufferInfo.size = size;
        bufferInfo.usage = usage;
        bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

        VK_CHECK_SUCCESS(vkCreateBuffer(
        m_device.handle(), &bufferInfo, nullptr, &buffer),
        "Failed to create buffer!"
        );

        VkMemoryRequirements memRequirements;
        vkGetBufferMemoryRequirements(m_device.handle(), buffer, &memRequirements);

        VkMemoryAllocateInfo allocInfo{};
        allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
        allocInfo.allocationSize = memRequirements.size;
        allocInfo.memoryTypeIndex = findMemoryType(memRequirements.memoryTypeBits, properties);

        VK_CHECK_SUCCESS(
            vkAllocateMemory(m_device.handle(), &allocInfo, nullptr, &bufferMemory),
            "Failed to allocate buffer memory!"
        );

        vkBindBufferMemory(m_device.handle(), buffer, bufferMemory, 0);
    }

    void MemoryAllocator::createImageWithInfo(
        const VkImageCreateInfo &imageInfo,
        VkMemoryPropertyFlags properties,
        VkImage &image, VkDeviceMemory
        &imageMemory) {
        VK_CHECK_SUCCESS(
            vkCreateImage(m_device.handle(), &imageInfo, nullptr, &image),
            "failed to create image!"
        );

        VkMemoryRequirements memRequirements;
        vkGetImageMemoryRequirements(m_device.handle(), image, &memRequirements);

        VkMemoryAllocateInfo allocInfo{};
        allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
        allocInfo.allocationSize = memRequirements.size;
        allocInfo.memoryTypeIndex = findMemoryType(memRequirements.memoryTypeBits, properties);

        VK_CHECK_SUCCESS(
            vkAllocateMemory(m_device.handle(), &allocInfo, nullptr, &imageMemory),
            "failed to allocate image memory!"
        );

        VK_CHECK_SUCCESS(
            vkBindImageMemory(m_device.handle(), image, imageMemory, 0),
            "failed to bind image memory!"
        );
    }

    VkCommandBuffer MemoryAllocator::beginSingleTimeCommands() {
        VkCommandBufferAllocateInfo allocInfo{};
        allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
        allocInfo.commandPool = m_device.commandPool();
        allocInfo.commandBufferCount = 1;

        VkCommandBuffer commandBuffer;
        vkAllocateCommandBuffers(m_device.handle(), &allocInfo, &commandBuffer);

        VkCommandBufferBeginInfo beginInfo{};
        beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
        beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

        vkBeginCommandBuffer(commandBuffer, &beginInfo);
        return commandBuffer;
    }

    void MemoryAllocator::endSingleTimeCommands(VkCommandBuffer commandBuffer) {
        vkEndCommandBuffer(commandBuffer);

        VkSubmitInfo submitInfo{};
        submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
        submitInfo.commandBufferCount = 1;
        submitInfo.pCommandBuffers = &commandBuffer;

        vkQueueSubmit(m_device.graphicsQueue(), 1, &submitInfo, VK_NULL_HANDLE);
        vkQueueWaitIdle(m_device.graphicsQueue());

        vkFreeCommandBuffers(m_device.handle(), m_device.commandPool(), 1, &commandBuffer);
    }

    void MemoryAllocator::copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size) {
        VkCommandBuffer commandBuffer = beginSingleTimeCommands();
        VkBufferCopy copyRegion{};
        copyRegion.size = size;
        vkCmdCopyBuffer(commandBuffer, srcBuffer, dstBuffer, 1, &copyRegion);

        endSingleTimeCommands(commandBuffer);
    }

    void MemoryAllocator::copyBufferToImage(
        VkBuffer buffer, VkImage image,
        uint32_t width, uint32_t height,
        uint32_t layerCount) {
        VkCommandBuffer commandBuffer = beginSingleTimeCommands();

        VkBufferImageCopy region{};
        region.bufferOffset = 0;
        region.bufferRowLength = 0;
        region.bufferImageHeight = 0;
        region.imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        region.imageSubresource.mipLevel = 0;
        region.imageSubresource.baseArrayLayer = 0;
        region.imageSubresource.layerCount = layerCount;
        region.imageOffset = {0, 0, 0};
        region.imageExtent = {width, height, 1};

        vkCmdCopyBufferToImage(commandBuffer, buffer, image,
                               VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &region);
        endSingleTimeCommands(commandBuffer);
    }
}
