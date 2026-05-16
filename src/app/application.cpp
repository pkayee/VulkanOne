

#include <memory>
#include <GLFW/glfw3.h>
#include <vk_one/app/application.h>

namespace vk_one {
    void Application::init() {
        ConfigManager configManager;
        WindowConfig config = configManager.parseJson(this->jsonFilePath);

        this->mainWindow = std::make_unique<Window>(&config);
        if (!this->mainWindow) { throw std::runtime_error("failed to create window "); }
    }

    void Application::run() {
        while (!mainWindow->windowShouldClose()) {
            glfwPollEvents();

        }

    }
}
