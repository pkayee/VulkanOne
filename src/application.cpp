

#include <memory>
#include <GLFW/glfw3.h>
#include "application.h"

namespace app {
    void MainApplication::init() {
        ConfigManager configManager;
        WindowConfig config = configManager.parseJson(this->jsonFilePath);

        this->mainWindow = std::make_unique<Window>(&config);
        if (!this->mainWindow) { throw std::runtime_error("failed to create window "); }
    }

    void MainApplication::run() {
        while (!mainWindow->windowShouldClose()) {
            glfwPollEvents();

        }

    }
}
