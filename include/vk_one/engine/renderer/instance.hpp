#pragma once

#include <vk_one/engine/renderer/renderer_pch.h>
#include <vk_one/engine/core/window.h>

namespace vk_one {

    class Instance {
    public:
        Instance(Window &window);
        ~Instance();
        Instance(const Instance &) = delete;
        Instance &operator=(const Instance &) = delete;
        Instance(Instance &&) = delete;
        Instance &operator=(Instance &&) = delete;

        VkInstance handle() { return  m_instance; }
        VkSurfaceKHR surface() { return  m_surface; }
    private:
        void createInstance();
        void setupDebugInstance();
        void createSurface();
        bool checkValidationLayerSupport();
        void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT &createInfo);
        void hasGflwRequiredInstanceExtensions();

        std::vector<const char *> getRequiredExtensions();
        const std::vector<const char *> validationLayers = { "VK_LAYER_KHRONOS_validation" };

        VkInstance m_instance;
        VkDebugUtilsMessengerEXT m_debugMessenger;
        VkSurfaceKHR m_surface;
        Window &m_window;
    };
}
