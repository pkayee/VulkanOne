#include <vk_one/engine/renderer/instance.hpp>
#include <vk_one/engine/renderer/utils.hpp>

namespace vk_one {
    void Instance::createSurface() {
        VK_CHECK_SUCCESS(
            glfwCreateWindowSurface(m_instance, m_window.handle(), nullptr, &m_surface),
            "Failed to create window surface!"
        );
    }
}
