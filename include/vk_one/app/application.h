#pragma once

#include <memory>

#include <vk_one/engine/core/window.h>
#include <vk_one/engine/config.h>

namespace vk_one {
    class Application {
    public:
        /* implement later
        Application();
        ~Application();
        */

        std::string jsonFilePath = "src/engine/configs.json";
        void init();
        void run();

    private:
        std::unique_ptr<Window> m_mainWindow;
    };

}
