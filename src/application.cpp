

#include <memory>
#include <GLFW/glfw3.h>
#include "application.h"
#include "config.h"

namespace app {
    void MainApplication::init() {
        ConfigManager configManager;
        WindowConfig config = configManager.parseJson(this->jsonFilePath);

        this->mainWindow = std::make_unique<Window>(
            config.width,
            config.height,
            config.name
            );
        if (!this->mainWindow) { throw std::runtime_error("failed to create window "); }
    }

    void MainApplication::run() {
        while (!mainWindow->windowShouldClose()) {
            glfwPollEvents();

        }

    }
}
