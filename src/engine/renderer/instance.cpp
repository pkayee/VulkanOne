#include <vk_one/engine/renderer/instance.hpp>
#include <vk_one/engine/utils.hpp>
#include <vk_one/engine/renderer/constants.hpp>

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
        auto func = (PFN_vkCreateDebugUtilsMessengerEXT) vkGetInstanceProcAddr(
            instance, "vkCreateDebugUtilsMessengerEXT");
        if (func != nullptr)
            return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
        return VK_ERROR_EXTENSION_NOT_PRESENT;
    }

    static void destroyDebugUtilsMessengerEXT(
        VkInstance instance,
        VkDebugUtilsMessengerEXT debugMessenger,
        const VkAllocationCallbacks *pAllocator) {
        auto func = (PFN_vkDestroyDebugUtilsMessengerEXT) vkGetInstanceProcAddr(
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
        auto &config = ConfigManager::instance();
        if (enableValidationLayers && !checkValidationLayerSupport()) {
            Log::throwRuntimeError("Cannot access validation layers!");
        }


        VkApplicationInfo appInfo{};
        auto appName = config.get<std::string>("application_config.name");
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = appName.c_str();
        appInfo.applicationVersion = VK_MAKE_VERSION(
            config.get<int>("application_config.version.major"),
            config.get<int>("application_config.version.minor"),
            config.get<int>("application_config.version.patch")
        );

        appInfo.pEngineName = "VulkanOne";
        appInfo.engineVersion = VK_MAKE_VERSION(
            config.get<int>("engine_config.version.major"),
            config.get<int>("engine_config.version.minor"),
            config.get<int>("engine_config.version.patch")
        );

        appInfo.apiVersion = VK_MAKE_API_VERSION(
            config.get<int>("api_config.version.variant"),
            config.get<int>("api_config.version.major"),
            config.get<int>("api_config.version.minor"),
            config.get<int>("api_config.version.patch")
        );

        VkInstanceCreateInfo createInfo = {};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo;

        auto extensions = getRequiredExtensions();
        createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
        createInfo.ppEnabledExtensionNames = Constants::validationLayers.data();

        VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo;
        if (enableValidationLayers) {
            createInfo.enabledLayerCount = static_cast<uint32_t>(Constants::validationLayers.size());
            createInfo.ppEnabledLayerNames = Constants::validationLayers.data();

            populateDebugMessengerCreateInfo(debugCreateInfo);
            createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT *) &debugCreateInfo;
        } else {
            createInfo.enabledLayerCount = 0;
            createInfo.pNext = nullptr;
        }

        VK_CHECK_SUCCESS(
            vkCreateInstance(&createInfo, nullptr, &m_instance),
            "Instance.cpp: Failed to create instance!"
        );

        hasGlfwRequiredInstanceExtensions();
    }

    void Instance::createSurface() {
        VK_CHECK_SUCCESS(
            glfwCreateWindowSurface(m_instance, m_window.handle(), nullptr, &m_surface),
            "Failed to create window surface!"
        );
    }

    void Instance::setupDebugMessenger() {
        if (!enableValidationLayers) {
            VkDebugUtilsMessengerCreateInfoEXT createInfo;
            populateDebugMessengerCreateInfo(createInfo);

            VK_CHECK_SUCCESS(
                createDebugUtilsMessengerEXT(m_instance, &createInfo, nullptr, &m_debugMessenger),
                "Instance.cpp: Failed to setup debug messenger!"
            );
        }
    }

    void Instance::populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT &createInfo) {
        createInfo = {};
        createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
        createInfo.messageSeverity =
                VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT
                |
                VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;

        createInfo.messageType =
                VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT
                |
                VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT
                |
                VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;

        createInfo.pfnUserCallback = debugCallback;
        createInfo.pUserData = nullptr;
    }

    bool Instance::checkValidationLayerSupport() {
        uint32_t layerCount;
        vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

        std::vector<VkLayerProperties> availableLayers(layerCount);
        vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

        for (const char *layerName: Constants::validationLayers) {
            bool layerFound = false;

            for (const auto &layerProperties: availableLayers) {
                if (strcmp(layerName, layerProperties.layerName)) {
                    layerFound = true;
                    break;
                }
            }

            if (!layerFound) return false;
        }
        return true;
    }

    std::vector<const char *> Instance::getRequiredExtensions() {
        uint32_t glfwExtensionCount = 0;
        const char **glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

        std::vector<const char *> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

        if (enableValidationLayers) { extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME); }

        return extensions;
    }

    void Instance::hasGlfwRequiredInstanceExtensions() {
        uint32_t extensionCount = 0;
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
        std::vector<VkExtensionProperties> extensions(extensionCount);
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());

        std::unordered_set<std::string> available;
        for (const auto &ext: extensions) { available.insert(ext.extensionName); }

        for (const auto &required: getRequiredExtensions()) {
            if (available.find(required) == available.end()) {
                std::string requiredExtension = required;
                Log::throwRuntimeError(
                    "Could not find required extensions: " + requiredExtension
                );
            }
        }
    }
}
