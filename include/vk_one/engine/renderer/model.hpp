#pragma once
#include <vk_one/engine/renderer/device.hpp>
#include <vk_one/engine/renderer/memory_allocator.hpp>
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <vector>

namespace vk_one {
    class Model {
    public:
        struct Vertex {
            glm::vec3 position{};
            glm::vec3 color{};

            static std::vector<VkVertexInputBindingDescription> getBindingDescriptions();

            static std::vector<VkVertexInputAttributeDescription> getAttributeDescriptions();
        };

        Model(Device &device, MemoryAllocator &allocator, const std::vector<Vertex> &vertices);

        ~Model();

        Model(const Model &) = delete;

        Model &operator=(const Model &) = delete;

        Model(Model &&) = delete;

        Model &operator=(Model &&) = delete;

        void bind(VkCommandBuffer commandBuffer);

        void draw(VkCommandBuffer commandBuffer);

    private:
        void createVertexBuffers(const std::vector<Vertex> &vertices);

        Device &m_device;
        MemoryAllocator &m_allocator;
        VkBuffer m_vertexBuffer;
        VkDeviceMemory m_vertexBufferMemory;
        uint32_t m_vertexCount;
    };
}
