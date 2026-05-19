/*
#include <vk_one/engine/renderer/instance.hpp>
#include <vk_one/engine/renderer/utils.hpp>

namespace vk_one {
    static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
    VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
    VkDebugUtilsMessageTypeFlagsEXT messageType,
    const VkDebugUtilsMessengerCallbackDataEXT *pCallbackData,
    void *pUserData) {
        std::cerr << "validation layer: " << pCallbackData->pMessage << std::endl;
        return VK_FALSE;
    }

    static VkResult createDebugUtilsMessengerEXT(
    VkInstance instance,
    const VkDebugUtilsMessengerCreateInfoEXT *pCreateInfo,
    const VkAllocationCallbacks *pAllocator,
    VkDebugUtilsMessengerEXT *pDebugMessenger) {
        auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(
            instance, "vkCreateDebugUtilsMessengerEXT");
        if (func != nullptr)
            return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
        return VK_ERROR_EXTENSION_NOT_PRESENT;
    }

    static void destroyDebugUtilsMessengerEXT(
    VkInstance instance,
    VkDebugUtilsMessengerEXT debugMessenger,
    const VkAllocationCallbacks *pAllocator) {
        auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(
            instance, "vkDestroyDebugUtilsMessengerEXT");
        if (func != nullptr)
            func(instance, debugMessenger, pAllocator);
    }

    Instance::Instance(Window &window) : m_window(window) {
        createInstance();
        setupDebugMessenger();
        createInstance();
    }

    Instance::~Instance() {
        if (enableValidationLayers) { destroyDebugUtilsMessengerEXT(m_instance, m_debugMessenger, nullptr); }
        vkDestroySurfaceKHR(m_instance, m_surface, nullptr);
        vkDestroyInstance(m_instance, nullptr);
    }

    void Instance::createInstance() {
        if (enableValidationLayers && !checkValidationLayerSupport()) {
            throw std::runtime_error("Cannot access validation layers!");
        }

        VkApplicationInfo appInfo{};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = "vk";

    }

    void Instance::createSurface() {
        VK_CHECK_SUCCESS(
            glfwCreateWindowSurface(m_instance, m_window.handle(), nullptr, &m_surface),
            "Failed to create window surface!"
        );
    }
}
*/