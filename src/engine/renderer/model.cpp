#include <vk_one/engine/renderer/model.hpp>
#include <vk_one/engine/utils.hpp>
#include <cassert>
#include <cstring>

namespace vk_one {
    Model::Model(Device &device, MemoryAllocator &allocator, const std::vector<Vertex> &vertices)
        : m_device(device), m_allocator(allocator) {
        createVertexBuffers(vertices);
    }

    Model::~Model() {
        vkDestroyBuffer(m_device.handle(), m_vertexBuffer, nullptr);
        vkFreeMemory(m_device.handle(), m_vertexBufferMemory, nullptr);
    }

    void Model::createVertexBuffers(const std::vector<Vertex> &vertices) {
        m_vertexCount = static_cast<uint32_t>(vertices.size());
        Log::assertLog(m_vertexCount >= 3, "Vertex Count must be greater than 3");

        VkDeviceSize bufferSize = sizeof(vertices[0]) * m_vertexCount;

        m_allocator.createBuffer(
            bufferSize,
            VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,
            VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
            m_vertexBuffer,
            m_vertexBufferMemory
        );

        void *data;
        vkMapMemory(m_device.handle(), m_vertexBufferMemory, 0, bufferSize, 0, &data);
        memcpy(data, vertices.data(), static_cast<size_t>(bufferSize));
        vkUnmapMemory(m_device.handle(), m_vertexBufferMemory);
    }

    void Model::bind(VkCommandBuffer commandBuffer) {
        VkBuffer buffers[] = {m_vertexBuffer};
        VkDeviceSize offsets[] = {0};
        vkCmdBindVertexBuffers(commandBuffer, 0, 1, buffers, offsets);
    }

    void Model::draw(VkCommandBuffer commandBuffer) {
        vkCmdDraw(commandBuffer, m_vertexCount, 1, 0, 0);
    }

    std::vector<VkVertexInputBindingDescription> Model::Vertex::getBindingDescriptions() {
        std::vector<VkVertexInputBindingDescription> bindingDescriptions(1);
        bindingDescriptions[0].binding = 0;
        bindingDescriptions[0].stride = sizeof(Vertex);
        bindingDescriptions[0].inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
        return bindingDescriptions;
    }

    std::vector<VkVertexInputAttributeDescription> Model::Vertex::getAttributeDescriptions() {
        std::vector<VkVertexInputAttributeDescription> attributeDescriptions(2);
        attributeDescriptions[0].binding = 0;
        attributeDescriptions[0].location = 0;
        attributeDescriptions[0].format = VK_FORMAT_R32G32B32_SFLOAT;
        attributeDescriptions[0].offset = offsetof(Vertex, position);

        attributeDescriptions[1].binding = 0;
        attributeDescriptions[1].location = 1;
        attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
        attributeDescriptions[1].offset = offsetof(Vertex, color);
        return attributeDescriptions;
    }
} // namespace vk_one
