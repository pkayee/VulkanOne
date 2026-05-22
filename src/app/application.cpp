

#include <memory>
#include <GLFW/glfw3.h>
#include <vk_one/app/application.h>

namespace vk_one {
    void Application::init() {
        auto& config = ConfigManager::instance();
        config.loadFromFile(CONFIG_PATH);

        m_mainWindow = std::make_unique<Window>(
            config.get<int>("window_config.width"),
            config.get<int>("window_config.height"),
            config.get<bool>("window_config.resizable"),
            config.get<std::string>("window_config.name")
        );
    }

    void Application::run() {
        while (!m_mainWindow->windowShouldClose()) {
            glfwPollEvents();
        }

    }
}
